#include "Rectangle.hpp"

namespace Gravy::System::Drawing
{
    Rectangle::Rectangle()
    {
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
    }

    Rectangle::Rectangle(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
};