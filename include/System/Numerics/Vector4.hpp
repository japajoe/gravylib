#ifndef GRAVY_VECTOR4_HPP
#define GRAVY_VECTOR4_HPP

#include "SIMD.hpp"

namespace Gravy::System::Numerics
{
    class Vector4
    {
    public:
        union 
        {
            struct 
            {
                float x, y, z, w;
            };
            SIMD128 value; // SIMD type for four single-precision floats
        };
        Vector4();
        Vector4(float x, float y, float z, float w);
        float Magnitude();
        void Normalize();
        static Vector4 Normalize(const Vector4 &v);
        static float Dot(const Vector4 &lhs, const Vector4 &rhs);
        static Vector4 Cross(const Vector4 &lhs, const Vector4 &rhs);
        static Vector4 Lerp(const Vector4 &a, const Vector4 &b, float t);
        Vector4 operator +(const Vector4 &rhs) const;
        Vector4 operator +(float rhs) const;
        Vector4& operator +=(const Vector4 &rhs);
        Vector4& operator +=(float rhs);        
        Vector4 operator -(const Vector4 &rhs) const;
        Vector4 operator -(float rhs) const;
        Vector4& operator -=(const Vector4 &rhs);
        Vector4& operator -=(float rhs);        
        Vector4 operator *(const Vector4 &rhs) const;
        Vector4 operator *(float rhs) const;
        Vector4& operator *=(const Vector4 &rhs);
        Vector4& operator *=(float rhs);
        Vector4 operator /(const Vector4 &rhs) const;
        Vector4 operator /(float rhs) const;
        Vector4& operator /=(const Vector4 &rhs);
        Vector4& operator /=(float rhs);
        bool operator ==(const Vector4 &rhs) const;
        bool operator !=(const Vector4 &rhs) const;
    };

    Vector4 operator +(float lhs, const Vector4 &rhs);
    Vector4 operator -(float lhs, const Vector4 &rhs);
    Vector4 operator *(float lhs, const Vector4 &rhs);
    Vector4 operator /(float lhs, const Vector4 &rhs);
};

#endif