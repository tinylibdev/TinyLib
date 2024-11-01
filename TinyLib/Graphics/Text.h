#pragma once
#include "../Base/BaseCategory.h"
#include "Drawable.h"


namespace tl
{
    class Text : public Drawable
    {
    public:
        Text(String = "", u32 = 12, Vec2i = {0, 0});
        ~Text();

        void setString(String);
        String getString() const;
        void setFontSize(s32);

    private:
        String string;
    };
}