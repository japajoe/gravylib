#include "Color.hpp"

namespace Gravy::System::Drawing
{
    Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    Color::Color()
    {
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->a = 255;
    }

    Color Color::LightGray()
    {
        return { 200, 200, 200, 255 };
    }

    Color Color::Gray()
    {
        return { 130, 130, 130, 255 };
    }

    Color Color::DarkGray()
    {
        return { 80, 80, 80, 255 };
    }

    Color Color::Yellow()
    {
        return { 253, 249, 0, 255 };
    }

    Color Color::Gold()
    {
        return { 255, 203, 0, 255 };
    }

    Color Color::Orange()
    {
        return { 255, 161, 0, 255 };
    }

    Color Color::Pink()
    {
        return { 255, 109, 194, 255 };
    }

    Color Color::Red()
    {
        return { 230, 41, 55, 255 };
    }

    Color Color::Maroon()
    {
        return { 190, 33, 55, 255 };
    }

    Color Color::Green()
    {
        return { 0, 228, 48, 255 };
    }

    Color Color::Lime()
    {
        return { 0, 158, 47, 255 };
    }

    Color Color::DarkGreen()
    {
        return { 0, 117, 44, 255 };
    }

    Color Color::SkyBlue()
    {
        return { 102, 191, 255, 255 };
    }

    Color Color::Blue()
    {
        return { 0, 121, 241, 255 };
    }

    Color Color::DarkBlue()
    {
        return { 0, 82, 172, 255 };
    }

    Color Color::Purple()
    {
        return { 200, 122, 255, 255 };
    }

    Color Color::Violet()
    {
        return { 135, 60, 190, 255 };
    }

    Color Color::DarkPurple()
    {
        return { 112, 31, 126, 255 };
    }

    Color Color::Beige()
    {
        return { 211, 176, 131, 255 };
    }

    Color Color::Brown()
    {
        return { 127, 106, 79, 255 };
    }

    Color Color::DarkBrown()
    {
        return { 76, 63, 47, 255 };
    }

    Color Color::White()
    {
        return { 255, 255, 255, 255 };
    }

    Color Color::Black()
    {
        return { 0, 0, 0, 255 };
    }

    Color Color::Blank()
    {
        return { 0, 0, 0, 0 };
    }

    Color Color::Magenta()
    {
        return { 255, 0, 255, 255 };
    }

    Color Color::RayWhite()
    {
        return { 245, 245, 245, 255 };
    }
};