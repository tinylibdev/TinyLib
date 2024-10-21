#include "Key.h"


namespace tl
{
    /// @brief Check if this key is currently down.
    /// @param key Which key to check, use enum tl::Key.
    /// @return True if this key is currently down.
    bit Key::isHeld(u8 key)
    {
        return (GetAsyncKeyState(key) & 0x8000) > 0;
    }
}