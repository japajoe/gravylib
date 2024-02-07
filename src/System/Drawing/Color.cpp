#include "Color.hpp"
#include "Math.hpp"

namespace Gravy::System::Drawing
{
    Color::Color()
    {
        this->r = 255;
        this->g = 255;
        this->b = 255;
        this->a = 255;
    }

    Color::Color(float r, float g, float b, float a)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;

        if(this->r > 0.0 && this->r > 1.0f)
            this->r /= 255.0f;
        if(this->g > 0.0 && this->g > 1.0f)
            this->g /= 255.0f;
        if(this->b > 0.0 && this->b > 1.0f)
            this->b /= 255.0f;
        if(this->a > 0.0 && this->a > 1.0f)
            this->a /= 255.0f;
    }

    Color::Color(uint32_t color)
    {
        this->r = (color >> 24) & 0xFF; // Extract red component
        this->g = (color >> 16) & 0xFF; // Extract green component
        this->b = (color >> 8) & 0xFF;  // Extract blue component
        this->a = color & 0xFF;          // Extract alpha component

        if(this->r > 0.0 && this->r > 1.0f)
            this->r /= 255.0f;
        if(this->g > 0.0 && this->g > 1.0f)
            this->g /= 255.0f;
        if(this->b > 0.0 && this->b > 1.0f)
            this->b /= 255.0f;
        if(this->a > 0.0 && this->a > 1.0f)
            this->a /= 255.0f;
    }

    Color Color::Lerp(const Color &a, const Color &b, float t)
    {
        Color c;
        c.r = Math::Lerp(a.r, b.r, t);
        c.g = Math::Lerp(a.g, b.g, t);
        c.b = Math::Lerp(a.b, b.b, t);
        c.a = Math::Lerp(a.a, b.a, t);
        return c;
    }

    Color Color::ToGrayScale(const Color &color)
    {
        float v = (color.r + color.g + color.b);
        if(v > 0.0f)
            v /= 3.0f;
        Color c;
        c.r = v;
        c.g = v;
        c.b = v;
        c.a = color.a;
        return c;
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