
#include "main.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/syscall.h>
#include <sys/uio.h>
#include <math.h>
#include <string.h>
#include "structs/include.h"



using namespace std;

using namespace ImGui;



bool main_thread_flag = true;

int abs_ScreenX = 0;
int abs_ScreenY = 0;
int game_pid = -1;
int getProcessID(const char *packageName) {
	int id = -1;
	DIR *dir;
	FILE *fp;
	char filename[64];
	char cmdline[64];
	struct dirent *entry;
	dir = opendir("/proc");
	while ((entry = readdir(dir)) != NULL)
	{
		id = atoi(entry->d_name);
		if (id != 0)
		{
			sprintf(filename, "/proc/%d/cmdline", id);
			fp = fopen(filename, "r");
			if (fp)
			{
				fgets(cmdline, sizeof(cmdline), fp);
				fclose(fp);
				if (strcmp(packageName, cmdline) == 0)
				{
					return id;
				}
			}
		}
	}
	closedir(dir);
	return -1;
}

uint64_t il2cpp_base = 0;

uint64_t get_module_base(const char *module_name, int mod) {
	uint64_t returned = 0;
	char path[32];
	sprintf(path, "/proc/%d/maps\0", game_pid);
	char line[1024];
	FILE* maps = fopen(path, "rt");
	while(fgets(line, 1024, maps)) {
		if(strstr(line, module_name) && strstr(line, (mod == 1 ? "r--p" : "r-xp"))) {
			uint64_t start,end;
			sscanf(line, "%lx-%lx",&start,&end);
			auto size = end - start;
			if(size >= 0x5100000) continue;
			returned = start;
			break;
		}
  }
  return returned;
}

template <typename T>
T rpm(uint64_t addr) {
    T value{};
    struct iovec local[1] = { { &value, sizeof(T) } };
    struct iovec remote[1] = { { (void*)addr, sizeof(T) } };

    if (syscall(__NR_process_vm_readv, game_pid, local, 1, remote, 1, 0) != sizeof(T)) {
        value = T{};
    }
    return value;
}

template <typename T>
void wpm(uint64_t addr, const T& value) {
    struct iovec local[1] = { { (void*)&value, sizeof(T) } };
    struct iovec remote[1] = { { (void*)addr, sizeof(T) } };

    syscall(__NR_process_vm_writev, game_pid, local, 1, remote, 1, 0);
}

typedef struct Matrix {
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
};


int CalcValue(int a1, int a2) { 
    if ((a1 & 1) != 0) { 
        return a1 ^ a2; 
    } else { 
        return (a2 & 0xFF00FF00) | ((uint8_t)a2 << 16) | ((a2 >> 16) & 0xFF); 
    } 
}

void WriteSafe(uintptr_t address, int value) {
    int a1 = rpm<int>(address);
    int encodedValue = CalcValue(a1, value);
    wpm<int>(address + 0x4, encodedValue);
}

std::string utf16le_to_utf8(const std::u16string &u16str) {    
    if (u16str.empty()) {
        return std::string();
    }

    const char16_t *p = u16str.data();   
    std::u16string::size_type len = u16str.length();  
    if (p[0] == 0xFEFF) {      
        p += 1;      
        len -= 1;   
    } 

    std::string u8str;   
    u8str.reserve(len * 3);    
    char16_t u16char;  
    for (std::u16string::size_type i = 0; i < len; ++i) {       
        u16char = p[i];        
        if (u16char < 0x0080) {          
            u8str.push_back((char) (u16char & 0x00FF));          
            continue;       
        }      
        if (u16char >= 0x0080 && u16char <= 0x07FF) {          
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));        
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));          
            continue;       
        }      
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {           
            uint32_t highSur = u16char;          
            uint32_t lowSur = p[++i];          
            uint32_t codePoint = highSur - 0xD800;    
            codePoint <<= 10;        
            codePoint |= lowSur - 0xDC00;      
            codePoint += 0x10000;           
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));     
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));         
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));            
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));        
            continue;       
        } { 
        u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));          
        u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));      
        u8str.push_back((char) ((u16char & 0x3F) | 0x80));         
        continue;      
        }    
    }   
    return u8str;
}

struct String {
    uint64_t klass;
    uint64_t monitor_data;
    int length;
    char first_char[ 256 ];

    std::string Get() {
        u16string utf16( ( char16_t * ) first_char, 0, length);

        std::string converted = utf16le_to_utf8( utf16 );

        return converted;
    }
};


#include "standoff/player.h"

#include "standoff/menu.h"



int main(int argc, char *argv[]) {
    game_pid = getProcessID("com.axlebolt.standoff2");
    if (game_pid <= 0) {
        printf("Game not found!",sizeof(Matrix)/sizeof(float));
        return -1;
    }
	
    screen_config();
    ::abs_ScreenX = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::abs_ScreenY = (displayInfo.height < displayInfo.width ? displayInfo.height : displayInfo.width);
    
    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height : displayInfo.width);
    if (!initGUI_draw(native_window_screen_x, native_window_screen_y, true)) {
        return -1;
    }
	il2cpp_base = get_module_base("libunity.so",1);
    
    Touch_Init(displayInfo.width, displayInfo.height, displayInfo.orientation, true);
   
	
    while (main_thread_flag) {
        drawBegin();
        {
			player();
            RenderMenu();
        }
		
		
        drawEnd();
        usleep(16000);
    }
	
    
    shutdown();
    Touch_Close();
    return 0;
} 
