#include "Bitset.h"


tl::Bitset::Bitset()
{
    data = 0;
}


tl::Bitset::~Bitset()
{

}


/// @brief Set the bit at index to value.
/// @param index Which bit will be set.
/// @param value True/false for the bit.
void tl::Bitset::set(u8 index, bit value)
{
    // Set to false
    if (!value)
        data &= ~(1 << index);
    else // Set to true
        data |= 1 << index;
}


/// @brief Get the value of the bit at index.
/// @param index Which bit to get.
/// @return If this bit is true or false.
tl::bit tl::Bitset::get(u8 index) const
{
    return (data >> index) & 1;
}


/// @brief Flip bit at index. True if false, false if true.
/// @param index Which bit to flip.
void tl::Bitset::flip(u8 index)
{
    data ^= 0b1 << index;
}


/// @brief Reset all bits in the bitset to off by default.
/// @param value True or false what the bitset is reset to.
void tl::Bitset::reset(tl::bit value)
{
    data = value * 255;
}