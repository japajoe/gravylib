#ifndef GRAVY_VECTOR2_HPP
#define GRAVY_VECTOR2_HPP

namespace Gravy::System::Numerics
{
    class Vector2
    {
    public:
        float x;
        float y;
        Vector2();
        Vector2(float x, float y);
        float Magnitude();
        void Normalize();
        static Vector2 Normalize(const Vector2 &v);
        static float Dot(const Vector2 &lhs, const Vector2 &rhs);
        static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
        Vector2 operator +(const Vector2 &rhs);
        Vector2 operator +(float rhs);        
        Vector2& operator +=(const Vector2 &rhs);
        Vector2& operator +=(float rhs);        
        Vector2 operator -(const Vector2 &rhs);
        Vector2 operator -(float rhs);        
        Vector2& operator -=(const Vector2 &rhs);
        Vector2& operator -=(float rhs);        
        Vector2 operator *(const Vector2 &rhs);
        Vector2 operator *(float rhs);        
        Vector2& operator *=(const Vector2 &rhs);
        Vector2& operator *=(float rhs);
        Vector2 operator /(const Vector2 &rhs);
        Vector2 operator /(float rhs);        
        Vector2& operator /=(const Vector2 &rhs);
        Vector2& operator /=(float rhs);
        bool operator ==(const Vector2 &rhs);
        bool operator !=(const Vector2 &rhs);
    };

    Vector2 operator +(float lhs, const Vector2 &rhs);
    Vector2 operator -(float lhs, const Vector2 &rhs);
    Vector2 operator *(float lhs, const Vector2 &rhs);
    Vector2 operator /(float lhs, const Vector2 &rhs);
};

#endif