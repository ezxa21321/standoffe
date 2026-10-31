#include <string>
#include <locale>
#include <codecvt>

inline std::string utf16le_to_utf8(const std::u16string &u16str) {    
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

struct string_t {
    void* m_pClass;
    void* m_pMonitor;
    uint32_t m_uLength;
    char16_t m_szBuffer[256];

    std::string get() {
        std::u16string utf16( ( char16_t * ) m_szBuffer, 0, m_uLength);

        std::string converted = utf16le_to_utf8( utf16 );

        return converted;
    }
	
	bool bIsValid() {
		return this && m_szBuffer && m_uLength > 0;
	}
	
	std::string sToUtf8() {
		if (bIsValid())
			return "";
			
		std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
		
		try {
			return converter.to_bytes(m_szBuffer, m_szBuffer + m_uLength);
		} catch (...) {
			return "";
		}
	}
	
	std::string sStr() {
		return sToUtf8();
	}
};
