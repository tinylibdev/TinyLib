#pragma once
#include "Drawable.h"
#include "../Base/BaseCategory.h"
#include "../Base/Win/WinAPI.h"


namespace tl
{
    // This class doesn't do much aside knowing it's a rectangle for now.
  class Rectangle : public Drawable
  {
    public:
      Rectangle(Vec4i bounds = {0, 0, 0, 0});
      ~Rectangle();
  };
}