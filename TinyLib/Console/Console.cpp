#include "Console.h"


namespace tl
{
    /// @brief Opens up a new console window.
    Console::Console()
    {
        create();
    }


    /// @brief Automatically closes the console when object is destroyed.
    Console::~Console()
    {
        close();
    }


    /// @brief Recreate the console window.
    void Console::create()
    {
        AllocConsole();
        stdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    }


    /// @brief Manually close the console window.
    void Console::close()
    {
        FreeConsole();
    }


    /// @brief Display a C-string in console.
    /// @param text What text to display.
    void Console::print(const char* text)
    {
        if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
        {
            unsigned long written = 0;
            WriteConsoleA(stdOut, text, strlen(text), &written, NULL);
        }
    }


    /// @brief Display a C-string in console with a new line after.
    /// @param text What text to display.
    void Console::println(const char* text)
    {
        print(text);
        print("\n");
    }


    /// @brief Display a number in console.
    /// @param num What number to display.
    void Console::print(u32 num)
    {
        char str[10];
        if (hexMode)
            wsprintfA(str, "%X", num);
        else
            wsprintfA(str, "%u", num);
        print(str);
    }


    /// @brief Display a number in console with a newline after.
    /// @param num What number to display.
    void Console::println(u32 num)
    {
        print(num);
        print("\n");
    }


    /// @brief Clear the console.
    void Console::clear()
    {
        if (stdOut != NULL && stdOut != INVALID_HANDLE_VALUE)
        {
            DWORD mode;
            GetConsoleMode(stdOut, &mode);
            SetConsoleMode(stdOut, mode | 4);
            unsigned long written = 0;
            WriteConsoleA(stdOut, "\x1b[2J\x1b[H", 7, &written, NULL);
        }
    }


    /// @brief Set certain settings for the console.
    /// @param index Console enum for setting.
    /// 
    /// Console has an enum with settings you can pass here to change
    /// some settings such as displaying numbers in decimal or hex format.
    void Console::set(u8 index)
    {
        if (index == Dec || index == Default)
            hexMode = false;
        else if (index == Hex)
            hexMode = true;
    }


    /// @brief Check if console is still open.
    /// @return True if console is open.
    bit Console::isOpen()
    {
        return GetConsoleWindow() != NULL;
    }
}