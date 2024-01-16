#include "System/Math.hpp"
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <random>

namespace Gravy::System
{
    std::random_device rdev;
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution<> idis(0, 255);

    uint32_t Math::lehmer = 0;
    bool Math::lehmerInitialized = false;

    double Math::Min(double a, double b)
    {
        return std::min(a, b);
    }

    double Math::Max(double a, double b)
    {
        return std::max(a, b);
    }

    void Math::SetRandomSeed()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 2147483647);
        
        int x = dist(rng);
        int y = dist(rng);

        if (x > 0 || y > 0)
            lehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);
    }

    void Math::SetRandomSeed(uint32_t x, uint32_t y)
    {
        if (x > 0 || y > 0)
            lehmer = (x & 0xFFFF) << 16 | (y & 0xFFFF);
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

    double Math::RandomRange(double min, double max)
    {
        double x = GetRandomLehmer() * (max - min);
        return min + x;
    }

    int32_t Math::RandomRange(int32_t min, int32_t max)
    {
        int32_t x = static_cast<int32_t>(GetRandomLehmer() * (max - min));
        return min + x;
    }

    uint8_t Math::RandomByte()
    {
        return static_cast<uint8_t>(idis(rgen));
    }

    double Math::GetRandomLehmer()
    {
        if(!lehmerInitialized)
        {
            lehmerInitialized = true;
            SetRandomSeed();
        }

        Math::lehmer += 0xe120fc15;
        uint64_t tmp;
        tmp = (uint64_t)Math::lehmer * 0x4a39b70d;
        uint32_t m1 = (tmp >> 32) ^ tmp;
        tmp = (uint64_t)m1 * 0x12fad5c9;
        uint32_t m2 = (tmp >> 32) ^ tmp;
        return (1.0 / 4294967295) * m2;
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