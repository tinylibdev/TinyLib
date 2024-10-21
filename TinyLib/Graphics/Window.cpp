#include "Window.h"


namespace tl
{
    /// @brief Windows API specific message processor.
    /// @param hwnd Window receiving event.
    /// @param msg The specific event to process.
    /// @param wParam 
    /// @param lParam 
    /// @return 
    /// 
    /// This requires a pointer back to the window, because otherwise we 
    /// cannot implement this as part of the Window class.
    LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (window == nullptr)
            return DefWindowProc(hwnd, msg, wParam, lParam);

        switch (msg)
        {
        case WM_CLOSE:
            window->currentEvents |= Event::Closed;
            return 0;
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
            break;
        case WM_MOVE:
            window->currentEvents |= Event::Moved;
            return 0;
            break;
        case WM_SIZE:
            window->currentEvents |= Event::Resized;
            return 0;
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }


    /// @brief Create a new window, all parameters are optional.
    /// @param size The width, height of this window in pixels.
    /// @param title The title of the window.
    /// @param style Additional window style flags.
    ///
    /// Size is optional, default is 800x600. 
    /// Title is optional, default is "Window".
    /// Style is optional, default is tl::Style::Default.
    Window::Window(Vec2i size, const char* title, LONG style)
    {
        create({size.x, size.y}, title, style);
    }


    /// @brief Clean up window resources.
    Window::~Window()
    {
        delete graphics;
        DestroyWindow(hwnd);
    }


    /// @brief Recreate the window.
    /// @param size The width, height of this window in pixels.
    /// @param title The title of the window.
    /// @param style Additional window style flags.
    ///
    /// All parameters are optional, any you don't provide will stay the same.
    void Window::create(Vec2i size, const char* title, LONG style)
    {
        // Create the window first
        WNDCLASSA wc = {};
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        char className[13];
        wsprintfA(className, "TL%u", GetCurrentProcessId());
        wc.lpszClassName = className;

        RegisterClassA(&wc);

        RECT rect = { 0, 0, size.x, size.y };
        AdjustWindowRect(&rect, style | WS_VISIBLE, FALSE);

        hwnd = CreateWindowA(
            wc.lpszClassName, title,
            style | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top,
            NULL, NULL, wc.hInstance, NULL
        );
        
#ifdef GDI_GRAPHICS
        graphics = new _GraphicsGDI(hwnd, size.x, size.y);
#else
        graphics = new _Graphics(hwnd, size.x, size.y);
#endif

        windowOpen = true;
        ShowWindow(hwnd, SW_SHOW);

        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    }


    /// @brief Check if the window is open.
    /// @return True if window is open.
    /// 
    /// This method also makes sure the program doesn't go past the FPS cap
    /// if set with Window::limitFPS().
    bool Window::isOpen()
    {
        if (maxFps > 0)
        {
            u64 currentTime = Time::currentTime();
            u64 frameDuration = 1000 / maxFps;
            if (currentTime - lastFrameTime < frameDuration)
                Sleep(frameDuration - (currentTime - lastFrameTime));
            lastFrameTime = Time::currentTime();
        }

        currentEvents = 0;

        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        return windowOpen;
    }


    /// @brief Draw a rectangle to the screen.
    /// @param rectangle The rectangle to draw.
    void Window::draw(Rectangle& rectangle)
    {
        graphics->draw(rectangle);
    }


    /// @brief Draw text to the screen.
    /// @param text The text you want to draw.
    void Window::draw(Text& text)
    {
        graphics->draw(text);
    }


    /// @brief Close this window.
    void Window::close()
    {
        windowOpen = false;
        DestroyWindow(hwnd);
    }


    /// @brief Clear the window.
    /// @param color Color to clear window with.
    void Window::clear(Color color)
    {
        graphics->clear(color);
    }


    /// @brief Display what you've drawn to the window.
    void Window::display()
    {
        graphics->display();
    }


    /// @brief Get size of the window.
    /// @return Width, height.
    Vec2i Window::getSize() const
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        return Vec2i(s32(rect.right), s32(rect.bottom));
    }


    /// @brief Set the size of the window.
    /// @param size Set the width, height of this window.
    void Window::setSize(Vec2i size)
    {
        SetWindowPos(hwnd, NULL, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOZORDER);
    }


    /// @brief Change the window title.
    /// @param title New title
    void Window::setTitle(const char* title)
    {
        SetWindowTextA(hwnd, title);
    }


    /// @brief Set the window's position on screen.
    /// @param pos New x, y position for the window.
    void Window::setPosition(Vec2i pos)
    {
        SetWindowPos(hwnd, NULL, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    }


    /// @brief Move the window from current position.
    /// @param pos Move the window by x, y.
    void Window::move(Vec2i pos)
    {
        setPosition({ getPosition().x + pos.x, getPosition().y + pos.y });
    }


    /// @brief Get the current position of the window.
    /// @return X-position, y-position.
    Vec2i Window::getPosition() const
    {
        RECT rect;
        GetWindowRect(hwnd, &rect);
        return Vec2i(s32(rect.left), s32(rect.top));
    }


    /// @brief Caps the framerate to given value, 0 for unlimited.
    /// @param fps Framerate cap.
    /// 
    /// FPS cap is enforced in Window::isOpen().
    void Window::limitFPS(u32 fps)
    {
        // TODO: FPS limiter seems to be off, I'll fix when I do unix time.
        maxFps = fps;
        if (maxFps > 0)
            lastFrameTime = Time::currentTime();
    }


    /// @brief Check if a window event activated this frame.
    /// @param event Window event to check.
    /// @return True if specified event activated this frame.
    /// 
    /// Events are an enum defined in Window.h, tl::Event.
    bit Window::checkEvent(u8 event)
    {
        return (currentEvents & event) > 0;
    }

    /*
    void Window::setScroll(Vec2i size)
    {
        SetScrollRange(hwnd, SB_HORZ, 0, size.x, TRUE);
        SetScrollRange(hwnd, SB_VERT, 0, size.y, TRUE);
    }


    Vec2i Window::getScroll()
    {
        Vec2i size;
        GetScrollRange(hwnd, SB_HORZ, nullptr, &size.x);
        GetScrollRange(hwnd, SB_VERT, nullptr, &size.y);

        return size;
    }
    */
}