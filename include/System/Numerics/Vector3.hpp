#ifndef GRAVY_VECTOR3_HPP
#define GRAVY_VECTOR3_HPP

#include "SIMD.hpp"

namespace Gravy::System::Numerics
{
    class Vector3
    {
    public:
        union 
        {
            struct 
            {
                float x, y, z;
            };
            SIMD128 value; // SIMD type for four single-precision floats
        };
        Vector3();
        Vector3(float x, float y, float z);
        float Magnitude();
        float Length();
        float LengthSquared();
        void Normalize();
        static Vector3 Normalize(const Vector3 &v);
        static float Dot(const Vector3 &lhs, const Vector3 &rhs);
        static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
        static Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t);
        Vector3 operator +(const Vector3 &rhs) const;
        Vector3 operator +(float rhs) const;
        Vector3& operator +=(const Vector3 &rhs);
        Vector3& operator +=(float rhs);        
        Vector3 operator -(const Vector3 &rhs) const;
        Vector3 operator -(float rhs) const;
        Vector3& operator -=(const Vector3 &rhs);
        Vector3& operator -=(float rhs);        
        Vector3 operator *(const Vector3 &rhs) const;
        Vector3 operator *(float rhs) const;
        Vector3& operator *=(const Vector3 &rhs);
        Vector3& operator *=(float rhs);
        Vector3 operator /(const Vector3 &rhs) const;
        Vector3 operator /(float rhs) const;
        Vector3& operator /=(const Vector3 &rhs);
        Vector3& operator /=(float rhs);
        bool operator ==(const Vector3 &rhs) const;
        bool operator !=(const Vector3 &rhs) const;
        Vector3 operator-() const;
    };

    Vector3 operator +(float lhs, const Vector3 &rhs);
    Vector3 operator -(float lhs, const Vector3 &rhs);
    Vector3 operator *(float lhs, const Vector3 &rhs);
    Vector3 operator /(float lhs, const Vector3 &rhs);
};

#endif