#ifndef GRAVY_QUATERNION_HPP
#define GRAVY_QUATERNION_HPP

#include "SIMD.hpp"
#include "Vector3.hpp"

namespace Gravy::System::Numerics
{
    class Quaternion
    {
    public:
        union 
        {
            Vector3 xyz;
            struct 
            {
                float x, y, z, w;
            };
            SIMD128 value; // SIMD type for four single-precision floats
        };
        Quaternion();
        Quaternion(float x, float y, float z, float w);
        Quaternion(float rotationX, float rotationY, float rotationZ);
        Quaternion(const Vector3 &v, float w);
        float Magnitude();
        float Length();
        float LengthSquared();
        void Normalize();
        Vector3 ToEulerAngles();
        static Vector3 ToEulerAngles(const Quaternion &value);
        static Quaternion Normalize(const Quaternion &value);
        static Quaternion FromAxisAngle(const Vector3 &axis, float angle);
        static Quaternion GetIdentity();
        static Quaternion Euler(float x, float y, float z);
        static Quaternion Euler(const Vector3 &eulerAngles);
        static Quaternion Slerp(const Quaternion &q1, const Quaternion &q2, float t);
        bool operator ==(const Quaternion &rhs) const;
        bool operator !=(const Quaternion &rhs) const;
        Quaternion operator-() const;
    };
};

#endif