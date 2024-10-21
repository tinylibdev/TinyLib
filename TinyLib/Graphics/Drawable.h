#pragma once
#include "../Base/Types.h"
#include "../Base/Win/WinAPI.h"


namespace tl
{
  // Forward declaration for the window intersect.
  class Window;

  class Drawable
  {
    public:
      Drawable(Vec4i bounds = {0, 0, 0, 0});
      ~Drawable();
      void setPosition(Vec2i);
      void setSize(Vec2i);
      Vec2i getPosition() const;
      Vec2i getSize() const;
      Color getColor() const;
      void move(Vec2i);
      void setColor(Color);
      bit intersects(Drawable&) const;
      bit intersects(Window&) const;

    protected:
      s32 posX, posY, sizeX, sizeY;
      u8 r = 0, g = 0, b = 0, a = 0;
  };
}