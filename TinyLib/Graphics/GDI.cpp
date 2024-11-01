#ifdef GDI_GRAPHICS
#include "GDI.h"


namespace tl
{
    _GraphicsGDI::_GraphicsGDI(HWND hwnd, s32 newWidth, s32 newHeight)
    {
        pHwnd = new HWND(hwnd);
        mainDC = GetDC(hwnd);
        offscreenDC = CreateCompatibleDC(mainDC);
        offscreenBitmap = CreateCompatibleBitmap(mainDC, newWidth, newHeight);
        SelectObject(offscreenDC, offscreenBitmap);
        width = newWidth;
        height = newHeight;
    }


    _GraphicsGDI::~_GraphicsGDI()
    {
        DeleteObject(offscreenBitmap);
        DeleteDC(offscreenDC);
        ReleaseDC(*pHwnd, mainDC);

        delete pHwnd;
    }


    void _GraphicsGDI::draw(Rectangle& rectangle)
    {
        Vec2i pos = rectangle.getPosition();
        Vec2i size = rectangle.getSize();
        Color color = rectangle.getColor();

        // Windows Rectangle
        RECT rect;
        rect.left = pos.x;
        rect.top = pos.y;
        rect.right = pos.x + size.x;
        rect.bottom = pos.y + size.y;

        // Set the brush color (optional)
        HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
        SelectObject(offscreenDC, brush);

        // Draw the rectangle
        FillRect(offscreenDC, &rect, brush);

        // Clean up
        DeleteObject(brush);
    }


    void _GraphicsGDI::draw(Text& text)
    {
        if (text.getString().cStr() == nullptr || text.getString().length() == 0) return;

        SetTextColor(offscreenDC, RGB(text.getColor().r, text.getColor().g, text.getColor().b));
        SetBkMode(offscreenDC, TRANSPARENT);

        HFONT hFont = CreateFont(text.getSize().y / 2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
        //HFONT hOldFont = (HFONT)SelectObject(offscreenDC, hFont);
        
        RECT space;
        space.left = text.getPosition().x;
        space.top = text.getPosition().y;
        space.right = space.left + text.getSize().x;
        space.bottom = space.top + text.getSize().y;

        DrawTextA(offscreenDC, text.getString().cStr(), -1, &space, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

        //SelectObject(offscreenDC, hOldFont);
        DeleteObject(hFont);
    }


    void _GraphicsGDI::clear(Color& color)
    {
        RECT rect;
        GetClientRect(*pHwnd, &rect);
        HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
        FillRect(offscreenDC, &rect, brush);
        DeleteObject(brush);
    }


    void _GraphicsGDI::display()
    {
        BitBlt(mainDC, 0, 0, width, height, offscreenDC, 0, 0, SRCCOPY);
    }
}
#endif