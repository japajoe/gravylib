#ifndef GRAVY_COLOR_HPP
#define GRAVY_COLOR_HPP

#include <cstdint>

namespace Gravy::System::Drawing
{
    struct Color
    {
        float r;
        float g;
        float b;
        float a;
        Color();
        Color(float r, float g, float b, float a);
        Color(uint32_t color);
        static Color Lerp(const Color &a, const Color &b, float t);
        static Color ToGrayScale(const Color &color);
        static Color LightGray();
        static Color Gray();
        static Color DarkGray();
        static Color Yellow();
        static Color Gold();
        static Color Orange();
        static Color Pink();
        static Color Red();
        static Color Maroon();
        static Color Green();
        static Color Lime();
        static Color DarkGreen();
        static Color SkyBlue();
        static Color Blue();
        static Color DarkBlue();
        static Color Purple();
        static Color Violet();
        static Color DarkPurple();
        static Color Beige();
        static Color Brown();
        static Color DarkBrown();
        static Color White();
        static Color Black();
        static Color Blank();
        static Color Magenta();
        static Color RayWhite();
    };
};

#endif