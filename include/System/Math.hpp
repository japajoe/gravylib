#ifndef GRAVY_MATHF_HPP
#define GRAVY_MATHF_HPP

#include <cstdint>

namespace Gravy::System
{
    class Math
    {
    public:
        static constexpr double PI = 3.14159265359;
        static constexpr double Rad2Deg = 180.0 / PI;
        static constexpr double Deg2Rad = PI / 180.0;

        static double Min(double a, double b);
        static double Max(double a, double b);        
        static double Abs(double value);
        static double Clamp(double value, double min, double max);
        static int32_t FloorToInt(double value);
        static double Floor(double value);
        static double InverseLerp(double start, double end, double value);
        static double Lerp(double start, double end, double percentage);
        static double Sin(double x);
        static double Cos(double x);
        static double Sqrt(double x);
        static double Pow(double x, double y);
        static double Atan2(double x, double y);
        static double Acos(double x);
        static double DegreesToRadians(double degrees);
        static double RadiansToDegrees(double radians);
        static double WrapAngleToRange(double a, double min, double max);
    };
};

#endif