#include "macros.h"

struct safeint_t
{
    int key;
    int value;

    int get()
    {
        if ((key & 1) == 0)
        {
            return value ^ key;
        }

        return BYTEn(value,2) | value & 0xFF00FF00 | (LOBYTE(value) << 16);
    }

    static void Write(uintptr_t address, int value)
    {
        int cryptoKey = Process::read<int>(address);
        cryptoKey &= ~1;
        Process::write(address, cryptoKey);
        Process::write(address + 4, (value ^ cryptoKey));
    }
};
