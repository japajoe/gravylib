#include "SIMD.hpp"

namespace Gravy::System::Numerics
{
    SIMD128 SIMD::Add(SIMD128 lhs, SIMD128 rhs)
    {
        return _mm_add_ps(lhs, rhs);
    }

    SIMD128 SIMD::Subtract(SIMD128 lhs, SIMD128 rhs)
    {
        return _mm_sub_ps(lhs, rhs);
    }

    SIMD128 SIMD::Multiply(SIMD128 lhs, SIMD128 rhs)
    {
        return _mm_mul_ps(lhs, rhs);
    }

    SIMD128 SIMD::Divide(SIMD128 lhs, SIMD128 rhs)
    {
        return _mm_div_ps(lhs, rhs);
    }

    SIMD128 SIMD::Add(SIMD128 lhs, float rhs)
    {
        return _mm_add_ps(lhs, _mm_set_ps1(rhs));
    }

    SIMD128 SIMD::Subtract(SIMD128 lhs, float rhs)
    {
        return _mm_sub_ps(lhs, _mm_set_ps1(rhs));
    }

    SIMD128 SIMD::Multiply(SIMD128 lhs, float rhs)
    {
        return _mm_mul_ps(lhs, _mm_set_ps1(rhs));
    }

    SIMD128 SIMD::Divide(SIMD128 lhs, float rhs)
    {
        return _mm_div_ps(lhs, _mm_set_ps1(rhs));
    }

    SIMD128 SIMD::Add(float lhs, SIMD128 rhs)
    {
        return _mm_add_ps(_mm_set_ps1(lhs), rhs);
    }

    SIMD128 SIMD::Subtract(float lhs, SIMD128 rhs)
    {
        return _mm_sub_ps(_mm_set_ps1(lhs), rhs);
    }

    SIMD128 SIMD::Multiply(float lhs, SIMD128 rhs)
    {
        return _mm_mul_ps(_mm_set_ps1(lhs), rhs);
    }

    SIMD128 SIMD::Divide(float lhs, SIMD128 rhs)
    {
        return _mm_div_ps(_mm_set_ps1(lhs), rhs);
    }    
};