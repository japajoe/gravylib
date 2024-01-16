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
        static void SetRandomSeed();
        static void SetRandomSeed(uint32_t x, uint32_t y);
        static double Abs(double value);
        static double Clamp(double value, double min, double max);
        static int32_t FloorToInt(double value);
        static double Floor(const double& value);
        static double InverseLerp(double start, double end, const double value);
        static double Lerp(double start, double end, const double percentage);
        static double RandomRange(double min, double max);
        static int32_t RandomRange(int32_t min, int32_t max);
        static uint8_t RandomByte();
        static double GetRandomLehmer();
        static double Sin(double x);
        static double Cos(double x);
        static double Sqrt(double x);
        static double Pow(double x, double y);
        static double Atan2(double x, double y);
        static double Acos(double x);
        static double DegreesToRadians(double degrees);
        static double RadiansToDegrees(double radians);
        static double WrapAngleToRange(double a, double min, double max);
    private:
        static uint32_t lehmer;
        static bool lehmerInitialized;
    };
};

#endif