#include "Text.h"


namespace tl
{
    /// @brief Create a new text that can be drawn to screen.
    /// @param str What the text displays.
    /// @param fontSize How big text is.
    /// @param pos Where text is.
    /// 
    /// The defaults for each parameter, no string data, fonst size 12,
    /// position (0, 0).
    Text::Text(String str, u32 fontSize, Vec2i pos)
    {
        setString(str);
        setFontSize(fontSize);
        setPosition(pos);
    }


    /// @brief Clean up string data.
    Text::~Text()
    {
    }


    /// @brief Set the string data.
    /// @param str New string for text.
    void Text::setString(String str)
    {
        string = str;
    }


    /// @brief Get the string data from this text.
    /// @return Internal string.
    String Text::getString() const
    {
        return string;
    }


    /// @brief Set the font size for this text.
    /// @param size New font size.
    /// 
    /// I might change how font size scales later on, it doesn't seem to be
    /// accurate based on pixels when using GDI/DirectX.
    void Text::setFontSize(s32 size)
    {
        setSize({ 2000, size * 2 });
    }
}