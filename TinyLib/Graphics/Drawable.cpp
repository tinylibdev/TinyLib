#include "Drawable.h"
#include "Window.h"


namespace tl
{
    /// @brief Creates a new drawable object with it's position and size.
    /// @param bounds Boundaries of this drawable, (width, height, left, top).
    Drawable::Drawable(Vec4i bounds)
    {
        setSize({ bounds.width, bounds.height });
        setPosition({bounds.left, bounds.top});
    }


    /// @brief Nothing to clean up for now.
    Drawable::~Drawable()
    {

    }


    /// @brief Set position of this drawable object.
    /// @param pos New x, y position for this drawable.
    void Drawable::setPosition(Vec2i pos)
    {
        posX = pos.x, posY = pos.y;
    }


    /// @brief Set size of this drawable object.
    /// @param size Set the width, height of this drawable.
    void Drawable::setSize(Vec2i size)
    {
        sizeX = size.x, sizeY = size.y;
    }


    /// @brief Get the current position of this drawable object.
    /// @return X-position, Y-position.
    Vec2i Drawable::getPosition() const
    {
        return { posX, posY };
    }


    /// @brief Get the current size of this drawable object.
    /// @return Width, height.
    Vec2i Drawable::getSize() const
    {
        return { sizeX, sizeY };
    }


    /// @brief Move this drawable object from current position.
    /// @param pos How far to move the x, y of this Drawable.
    /// 
    /// Sets position relative to current position offset by x and y parameters.
    void Drawable::move(Vec2i pos)
    {
        posX += pos.x, posY += pos.y;
    }


    /// @brief Set the color of this drawable object.
    /// @param color New color for this object.
    void Drawable::setColor(Color color)
    {
        r = color.r, g = color.g, b = color.b, a = color.a;
    }


    /// @brief Get the current color of this drawable object.
    /// @return Current color.
    Color Drawable::getColor() const
    {
        return { r, g, b, a };
    }


    /// @brief Check if this drawable is intersecting with another.
    /// @param other The drawable object to compare with this one.
    /// @return True if both objects intersect.
    /// 
    /// Compares the boundaries of both drawable objects. Using position and
    /// size, if they overlap anywhere, then this is true for an intersection.
    bit Drawable::intersects(Drawable& other) const
    {
        return posX < other.posX + other.sizeX &&
            posX + sizeX > other.posX &&
            posY < other.posY + other.sizeY &&
            posY + sizeY > other.posY;
    }


    /// @brief Check if this drawable is inside the window.
    /// @param window The window to compare with.
    /// @return True if this drawable is inside window.
    /// 
    /// If this drawable is fully outside window (not visible), then it will
    /// return false. Helpful for rendering only on-screen objects.
    bit Drawable::intersects(Window& window) const
    {
        return posX < window.getSize().x &&
            posX + sizeX > 0 &&
            posY < window.getSize().y &&
            posY + sizeY > 0;
    }
}