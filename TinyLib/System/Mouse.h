#pragma once
#include "../Base/BaseCategory.h"
#include "../Graphics/Drawable.h"
#include "../Base/Win/WinAPI.h"


namespace tl
{
    class Mouse
    {
    public:
        // Enum for different mouse buttons
        enum
        {
            Left = VK_LBUTTON,
            Right = VK_RBUTTON,
            Middle = VK_MBUTTON
        };

        static bit isHeld(u8);
        static Vec2i getPosition();
        static bit intersects(Drawable&);
    };
}