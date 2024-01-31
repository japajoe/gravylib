#ifndef GRAVY_VECTOR2_HPP
#define GRAVY_VECTOR2_HPP

#include "SIMD.hpp"

namespace Gravy::System::Numerics
{
    class Vector2
    {
    public:
        union 
        {
            struct 
            {
                float x, y;
            };
            SIMD128 value; // SIMD type for four single-precision floats
        };
        Vector2();
        Vector2(float x, float y);
        float Magnitude();
        void Normalize();
        static Vector2 Normalize(const Vector2 &v);
        static float Dot(const Vector2 &lhs, const Vector2 &rhs);
        static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
        Vector2 operator +(const Vector2 &rhs) const;
        Vector2 operator +(float rhs) const;
        Vector2& operator +=(const Vector2 &rhs);
        Vector2& operator +=(float rhs);        
        Vector2 operator -(const Vector2 &rhs) const;
        Vector2 operator -(float rhs) const;
        Vector2& operator -=(const Vector2 &rhs);
        Vector2& operator -=(float rhs);        
        Vector2 operator *(const Vector2 &rhs) const;
        Vector2 operator *(float rhs) const;
        Vector2& operator *=(const Vector2 &rhs);
        Vector2& operator *=(float rhs);
        Vector2 operator /(const Vector2 &rhs) const;
        Vector2 operator /(float rhs) const;
        Vector2& operator /=(const Vector2 &rhs);
        Vector2& operator /=(float rhs);
        bool operator ==(const Vector2 &rhs) const;
        bool operator !=(const Vector2 &rhs) const;
    };

    Vector2 operator +(float lhs, const Vector2 &rhs);
    Vector2 operator -(float lhs, const Vector2 &rhs);
    Vector2 operator *(float lhs, const Vector2 &rhs);
    Vector2 operator /(float lhs, const Vector2 &rhs);
};

#endif