#ifdef GDI_GRAPHICS
#pragma once
#include "../Base/Win/WinAPI.h"
#include "Rectangle.h"
#include "../Base/BaseCategory.h"
#include "Text.h"


namespace tl
{
    class _GraphicsGDI
    {
    public:
        _GraphicsGDI(HWND, s32, s32);
        ~_GraphicsGDI();

        void draw(Rectangle&);
        void draw(Text&);
        void clear(Color&);
        void display();

    private:
        HWND* pHwnd = nullptr;
        s32 width, height;
        HDC offscreenDC;
        HDC mainDC;
        HBITMAP offscreenBitmap;
    };
}
#endif