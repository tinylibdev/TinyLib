#pragma once
#include "../Base/Win/WinAPI.h"
#include "Drawable.h"
#include "Rectangle.h"
#include "Graphics.h"
#include "GDI.h"
#include "Text.h"
#include "../Base/BaseCategory.h"


namespace tl
{
    enum Event
    {
        Closed = 0b1,
        Moved = 0b10,
        Resized = 0b100
    };


    enum Style
    {
        Border = WS_BORDER,
        Title = WS_CAPTION,
        //HScroll = WS_HSCROLL,
        //VScroll = WS_VSCROLL,
        Background = WS_MINIMIZE,
        Fullscreen = WS_MAXIMIZE,
        Minimize = WS_MINIMIZEBOX,
        Maximize = WS_MAXIMIZEBOX,
        Resize = WS_SIZEBOX,
        Default = WS_OVERLAPPEDWINDOW
    };

    class Window
    {
    public:
        Window(Vec2i = {800, 600}, const char* = "Window", LONG style = WS_OVERLAPPEDWINDOW);
        ~Window();

        void create(Vec2i = {800, 600}, const char* = "Window", LONG style = WS_OVERLAPPEDWINDOW);
        bool isOpen();
        void draw(Rectangle& rectangle);
        void draw(Text& text);
        void close();
        void clear(Color color = Color(255, 255, 255, 255));
        Vec2i getSize() const;
        void setSize(Vec2i);
        void setTitle(const char* title);
        void setPosition(Vec2i);
        void move(Vec2i);
        Vec2i getPosition() const;
        void display();
        void limitFPS(u32 fps);
        bit checkEvent(u8 event);
        //void setScroll(Vec2i = { 0, 0 });
        //Vec2i getScroll();

    private:
        HWND hwnd;
        bool windowOpen;
        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        u16 maxFps = 0;
        u64 lastFrameTime;
        u8 currentEvents;
#ifdef GDI_GRAPHICS
        _GraphicsGDI* graphics = nullptr;
#else
        _Graphics* graphics = nullptr;
#endif
    };
}