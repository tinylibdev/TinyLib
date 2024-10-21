#pragma once
#include "../Base/BaseCategory.h"
#include "Drawable.h"


namespace tl
{
    class Text : public Drawable
    {
    public:
        Text(const ascii* = nullptr, u32 = 12, Vec2i = { 0, 0 });
        ~Text();

        void setString(const ascii*);
        ascii* getString() const;
        void setFontSize(s32);

    private:
        ascii* string;
    };
}