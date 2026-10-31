#include "macros.h"

struct safebool_t
{
    int key;
    int value;

    bool get()
    {
        if ((key & 1) == 0)
        {
            return (value ^ key) == 1;
        }
        return (BYTEn(value,2) | value & 0xFF00FF00 | (LOBYTE(value) << 16)) == 1;
    }

    static void Write(uintptr_t address, bool value, bool nullable = false)
    {
        address = nullable ? Process::read<uintptr_t>(address + 4) : address;
        int cryptoKey = Process::read<int>(address);
        cryptoKey &= ~1;
        Process::write(address, cryptoKey);
        Process::write(address + 4, (value ^ cryptoKey));
    }
};
