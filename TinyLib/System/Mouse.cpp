#include "Mouse.h"


namespace tl
{
    /// @brief Check if a mouse button is currently down.
    /// @param button Which mouse button to check.
    /// @return True if that mouse button is down.
    /// 
    /// tl::Mouse has an enum for different mouse buttons.
    bit Mouse::isHeld(u8 button)
    {
        return (GetAsyncKeyState(button) & 0x8000) != 0;
    }


    /// @brief Get current position of the mouse cursor.
    /// @return X-position, Y-position.
    Vec2i Mouse::getPosition()
    {
        HWND hwnd = GetForegroundWindow();
        POINT cursorPos;

        GetCursorPos(&cursorPos);
        ScreenToClient(hwnd, &cursorPos);

        return { cursorPos.x, cursorPos.y };
    }


    /// @brief Check if the mouse cursor is inside a drawable object.
    /// @param other Drawable to check.
    /// @return True if the mouse cursor is pointed at the parameter.
    bit Mouse::intersects(Drawable& other)
    {
        Vec2i cursorPos = getPosition();
        Vec2i drawablePos = other.getPosition();
        Vec2i drawableSize = other.getSize();

        return cursorPos.x >= drawablePos.x &&
            cursorPos.x <= drawablePos.x + drawableSize.x &&
            cursorPos.y >= drawablePos.y &&
            cursorPos.y <= drawablePos.y + drawableSize.y;
    }
}