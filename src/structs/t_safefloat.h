#include "macros.h"

struct safefloat_t
{
    int key;
    int value;

    union fi { float f; int i; };

    float get()
    {
        fi vV;
        if ((key & 1) == 0)
        {
            vV.i = value ^ key;
            return vV.f;
        }
        vV.i = BYTEn(value,2) | value & 0xFF00FF00 | (LOBYTE(value) << 16);
        return vV.f;
    }

    static void Write(uintptr_t address, float value)
    {
        int cryptoKey = Process::read<int>(address);
        cryptoKey |= 1;
        fi v;
        v.f = value;

        fi v2;
        v2.i = (v.i ^ cryptoKey);

        Process::write(address, cryptoKey);
        Process::write(address + 4, v2.f);
    }
};
