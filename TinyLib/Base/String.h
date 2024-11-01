#pragma once
#include "Types.h"
#include "Win/WinAPI.h"


namespace tl
{
    class String
    {
    public:
        String(const ascii* = "");
        String(u32);
        String(s32);
        ~String();

        u16 length() const;
        const ascii* cStr() const;

        const ascii operator[](u16 index) const
        {
            return text[index];
        }
        const ascii& operator[](u16 index)
        {
            return text[index];
        }

        String(const String& other);
        String& operator=(const String& other);
        String operator+(String other);
        void operator+=(String other);
        String operator+(s32 num);
        void operator+=(s32 num);
        String operator+(u32 num);
        void operator+=(u32 num);

    private:
        u16 size;
        ascii* text;

        template <typename T>
        String numberToString(T);
        void create(const ascii*);
    };
}