/*
* This file contains custom typedefs for a more standard type naming system.
* These are used internally and may be used by the user of this library as well.
* If there's a conflict for a specific C type between systems, we unify them.
* All numbers also have the range they can have in a comment for IDEs to see.
* More advanced types like String and Bitset have their own class files.
* Except I haven't added back String or Bitset since a recent redesign, they'll return.
*/

#pragma once

namespace tl
{
    // -127 : 128
    using s8 = signed char;

    // -32,767 : 32,768
    using s16 = signed short;

    // -2,147,483,647 : 2,147,483,648
    using s32 = signed int;

    // -9,223,372,036,854,775,807 : 9,223,372,036,854,775,808
#ifdef _MSC_VER
    using s64 = signed __int64;
#else
    using s64 = signed long long;
#endif

    // 0 : 255
    using u8 = unsigned char;

    // 0 : 65,535
    using u16 = unsigned short;

    // 0 : 4,294,967,295
    using u32 = unsigned int;

    // 0 : 18,446,744,073,709,551,616
#ifdef _MSC_VER
    using u64 = unsigned __int64;
#else
    using u64 = unsigned long long;
#endif

    // Can have up to 7 real decimals.
    using f32 = float;

    // Can have up to 15 real decimals.
    using f64 = double;

    // A single ASCII character.
    using ascii = char;

    // A single unicode character.
    using unicode = wchar_t;

    // A true/false value.
    // This actually takes 1 byte of data if used.
    // If you want to make full usage of a byte use tl::bitset
    using bit = bool;

    // A vector of 2 signed integers.
    struct Vec2i
    {
        s32 x, y;

        Vec2i(s32 xValue = 0, s32 yValue = 0)
        {
            x = xValue;
            y = yValue;
        }
    };


    // A vector of 3 signed integers.
    struct Vec3i
    {
        s32 x, y, z;

        Vec3i(s32 xValue = 0, s32 yValue = 0, s32 zValue = 0)
        {
            x = xValue;
            y = yValue;
            z = zValue;
        }
    };


    // A vector of 4 signed integers. Usually for a rectangle or boundaries.
    struct Vec4i
    {
        s32 width, height, left, top;

        Vec4i(s32 newWidth = 0, s32 newHeight = 0, s32 newLeft = 0, s32 newTop = 0)
        {
            width = newWidth;
            height = newHeight;
            left = newLeft;
            top = newTop;
        }
    };


    // A color with 4 channels.
    struct Color
    {
        u8 r, g, b, a;

        Color(u8 red = 0, u8 green = 0, u8 blue = 0, u8 alpha = 255)
        {
            r = red;
            g = green;
            b = blue;
            a = alpha;
        }
    };
}