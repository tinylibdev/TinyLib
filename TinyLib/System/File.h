#pragma once
#include "../Base/Win/WinAPI.h"
#include "../Base/BaseCategory.h"


namespace tl
{
    class File
    {
    public:
        File();
        File(const char* path);
        ~File();

        void open(const char* path);
        void close();
        void read(char** data);
        //void write();
        size_t length();

    private:
        const char* path;
    };
}
