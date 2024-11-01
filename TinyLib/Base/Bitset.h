#pragma once
#include "Types.h"


namespace tl
{
    class Bitset
    {
    public:
        Bitset();
        ~Bitset();

        void set(u8, bit);
        bit get(u8) const;
        void flip(u8);
        void reset(bit = false);

        /* Will implement later
        bit operator[](const u8& pos) const
        {

        }
        */

    private:
        u8 data;
    };
}