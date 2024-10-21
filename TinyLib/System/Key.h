#pragma once
#include "../Base/Win/WinAPI.h"
#include "../Base/Types.h"


namespace tl
{
    class Key
    {
    public:
        static bit isHeld(u8 key);
        //static bit isPressed(u8 key);
        //static bit isReleased(u8 key);

        /// @brief Readable version for every standard keyboard key.
        enum
        {
            Space = VK_SPACE,
            A = 0x41,
            B = 0x42,
            C = 0x43,
            D = 0x44,
            E = 0x45,
            F = 0x46,
            G = 0x47,
            H = 0x48,
            I = 0x49,
            J = 0x4A,
            K = 0x4B,
            L = 0x4C,
            M = 0x4D,
            N = 0x4E,
            O = 0x4F,
            P = 0x50,
            Q = 0x51,
            R = 0x52,
            S = 0x53,
            T = 0x54,
            U = 0x55,
            V = 0x56,
            W = 0x57,
            X = 0x58,
            Y = 0x59,
            Z = 0x5A,
            Num0 = 0x30,
            Num1 = 0x31,
            Num2 = 0x32,
            Num3 = 0x33,
            Num4 = 0x34,
            LShift = VK_LSHIFT,
            RShift = VK_RSHIFT,
            LControl = VK_LCONTROL,
            RControl = VK_RCONTROL,
            LAlt = VK_LMENU,
            RAlt = VK_RMENU,
            Up = VK_UP,
            Down = VK_DOWN,
            Left = VK_LEFT,
            Right = VK_RIGHT
        };
    };
}