#ifndef GRAVY_RANDOM_HPP
#define GRAVY_RANDOM_HPP

#include <cstdint>

namespace Gravy::System
{
    class Random
    {
    public:
        static void Seed(uint32_t seed);
        static double GetNextDouble();
        static uint8_t GetNextByte();
        static double Range(double min, double max);
    };
};

#endif