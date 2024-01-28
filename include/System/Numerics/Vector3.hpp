#ifndef GRAVY_VECTOR3_HPP
#define GRAVY_VECTOR3_HPP

namespace Gravy::System::Numerics
{
    class Vector3
    {
    public:
        float x;
        float y;
        float z;
        Vector3();
        Vector3(float x, float y, float z);
        float Magnitude();
        void Normalize();
        static Vector3 Normalize(const Vector3 &v);
        static float Dot(const Vector3 &lhs, const Vector3 &rhs);
        static Vector3 Cross(const Vector3 &lhs, const Vector3 &rhs);
        static Vector3 Lerp(const Vector3 &a, const Vector3 &b, float t);
        Vector3 operator +(const Vector3 &rhs);
        Vector3 operator +(float rhs);        
        Vector3& operator +=(const Vector3 &rhs);
        Vector3& operator +=(float rhs);        
        Vector3 operator -(const Vector3 &rhs);
        Vector3 operator -(float rhs);        
        Vector3& operator -=(const Vector3 &rhs);
        Vector3& operator -=(float rhs);        
        Vector3 operator *(const Vector3 &rhs);
        Vector3 operator *(float rhs);        
        Vector3& operator *=(const Vector3 &rhs);
        Vector3& operator *=(float rhs);
        Vector3 operator /(const Vector3 &rhs);
        Vector3 operator /(float rhs);        
        Vector3& operator /=(const Vector3 &rhs);
        Vector3& operator /=(float rhs);
        bool operator ==(const Vector3 &rhs);
        bool operator !=(const Vector3 &rhs);
    };

    Vector3 operator +(float lhs, const Vector3 &rhs);
    Vector3 operator -(float lhs, const Vector3 &rhs);
    Vector3 operator *(float lhs, const Vector3 &rhs);
    Vector3 operator /(float lhs, const Vector3 &rhs);
};

#endif