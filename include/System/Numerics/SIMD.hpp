#ifndef GRAVY_SIMD_HPP
#define GRAVY_SIMD_HPP

#include <immintrin.h>

namespace Gravy::System::Numerics
{
    typedef  __m128 SIMD128;

    class SIMD
    {
    public:
        static SIMD128 Add(SIMD128 lhs, SIMD128 rhs);
        static SIMD128 Subtract(SIMD128 lhs, SIMD128 rhs);
        static SIMD128 Multiply(SIMD128 lhs, SIMD128 rhs);
        static SIMD128 Divide(SIMD128 lhs, SIMD128 rhs);
        
        static SIMD128 Add(SIMD128 lhs, float rhs);
        static SIMD128 Subtract(SIMD128 lhs, float rhs);
        static SIMD128 Multiply(SIMD128 lhs, float rhs);
        static SIMD128 Divide(SIMD128 lhs, float rhs);
        
        static SIMD128 Add(float lhs, SIMD128 rhs);
        static SIMD128 Subtract(float lhs, SIMD128 rhs);
        static SIMD128 Multiply(float lhs, SIMD128 rhs);
        static SIMD128 Divide(float lhs, SIMD128 rhs);

    };
};

#endif