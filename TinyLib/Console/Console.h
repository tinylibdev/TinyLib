#pragma once
#include "../Base/Win/WinAPI.h"
#include "../Base/BaseCategory.h"


namespace tl
{
    class Console
    {
    public:
        Console();
        ~Console();

        void create();
        void close();
        void print(const char*);
        void println(const char*);
        void print(u32);
        void println(u32);
        void clear();
        void set(u8);
        bit isOpen();

        enum
        {
            Default = 0,
            Dec = 1,
            Hex = 2
        };

    private:
        HANDLE stdOut;
        bit hexMode = false;
    };
}