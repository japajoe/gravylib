#include "System/Math.hpp"
#include <algorithm>
#include <stdlib.h>
#include <math.h>

namespace Gravy::System
{
    double Math::Min(double a, double b)
    {
        return std::min(a, b);
    }

    double Math::Max(double a, double b)
    {
        return std::max(a, b);
    }

    double Math::Abs(double value)
    {
        return abs(value);
    }

    double Math::Clamp(double value, double min, double max)
    {
        if(value < min)
            value = min;
        if(value > max)
            value = max;
        return value;
    }

    int32_t Math::FloorToInt(double value)
    {
        return static_cast<int32_t>(floor(value));
    }

    double Math::Floor(double value)
    {
        return floor(value);
    }

    double Math::InverseLerp(double start, double end, double value)
    {
        return (value - start) / (end - start);
    }

    double Math::Lerp(double start, double end, double percentage)
    {
        return start + ((end-start) * percentage);	
    }

    double Math::Sin(double x)
    {
        return sinf(x);
    }

    double Math::Cos(double x)
    {
        return cosf(x);
    }

    double Math::Sqrt(double x)
    {
        return sqrt(x);
    }

    double Math::Pow(double x, double y)
    {
        return pow(x, y);
    }

    double Math::Atan2(double x, double y)
    {
        return atan2(x, y);
    }

    double Math::Acos(double x)
    {
        return acos(x);
    }

    double Math::DegreesToRadians(double degrees)
    {
        return Math::Deg2Rad * degrees;
    }

    double Math::RadiansToDegrees(double radians)
    {
        return Math::Rad2Deg * radians;
    }

    double Math::WrapAngleToRange(double a, double min, double max)
    {
        double result = a + 0;
        double range = (max - min);
        while(result >= max)
            result -= range;
        while(result < min)
            result += range;
        return result;
    }
}