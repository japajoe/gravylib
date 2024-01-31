#ifndef GRAVY_COLOR_HPP
#define GRAVY_COLOR_HPP

#include <cstdint>

namespace Gravy::System::Drawing
{
    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        Color();
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