#ifndef GRAVY_RECTANGLE_HPP
#define GRAVY_RECTANGLE_HPP

namespace Gravy::System::Drawing
{
    struct Rectangle
    {
        float x;
        float y;
        float width;
        float height;
        Rectangle();
        Rectangle(float x, float y, float width, float height);
    };
};

#endif