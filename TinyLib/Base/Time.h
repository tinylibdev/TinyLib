#pragma once
#include "Types.h"
#include "../Base/Win/WinAPI.h"


namespace tl
{
    class Time
    {
    public:
        Time();
        Time(u64 timeValue);
        ~Time();

        u64 getTime();
        void update();

        static u64 currentTime();

    private:
        u64 time;
    };
}