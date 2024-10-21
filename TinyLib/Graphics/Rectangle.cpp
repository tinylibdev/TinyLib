#include "Rectangle.h"


namespace tl
{
    /// @brief Creates a new rectangle with drawable constructor.
    /// @param bounds Boundaries of this rectangle, (width, height, left, top).
    Rectangle::Rectangle(Vec4i bounds)
        : Drawable(bounds)
    {

    }


    /// @brief Nothing to clean up for now.
    Rectangle::~Rectangle()
    {

    }
}