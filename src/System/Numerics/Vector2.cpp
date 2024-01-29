#include "Vector2.hpp"
#include <cmath>

namespace Gravy::System::Numerics
{
    Vector2::Vector2()
    {
        this->x = 0;
        this->y = 0;
    }
    
    Vector2::Vector2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    float Vector2::Magnitude()
    {
        return std::sqrt(x * x + y * y);
    }

    void Vector2::Normalize()
    {
        float scale = 1.0f / Magnitude();
        value = _mm_mul_ps(value, _mm_set_ps1(scale));
    }

    Vector2 Vector2::Normalize(const Vector2 &v)
    {
        Vector2 normalized = v;
        float scale = 1.0f / normalized.Magnitude();
        normalized.value = _mm_mul_ps(normalized.value, _mm_set_ps1(scale));
        return normalized;
    }

    float Vector2::Dot(const Vector2 &lhs, const Vector2 &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    Vector2 Vector2::Lerp(const Vector2 &a, const Vector2 &b, float t)
    {
        Vector2 c;
        c.x = t * (b.x - a.x) + a.x;
        c.y = t * (b.y - a.y) + a.y;
        return c;
    }

    Vector2 Vector2::operator +(const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_add_ps(value, rhs.value);
        return v;
    }

    Vector2 Vector2::operator +(float rhs)
    {
        Vector2 v;
        v.value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector2& Vector2::operator +=(const Vector2 &rhs)
    {
        value = _mm_add_ps(value, rhs.value);
        return *this;
    }

    Vector2& Vector2::operator +=(float rhs)
    {
        value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector2 Vector2::operator -(const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_sub_ps(value, rhs.value);
        return v;
    }

    Vector2 Vector2::operator -(float rhs)
    {
        Vector2 v;
        v.value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector2& Vector2::operator -=(const Vector2 &rhs)
    {
        value = _mm_sub_ps(value, rhs.value);
        return *this;
    }

    Vector2& Vector2::operator -=(float rhs)
    {
        value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector2 Vector2::operator *(const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_mul_ps(value, rhs.value);
        return v;
    }

    Vector2 Vector2::operator *(float rhs)
    {
        Vector2 v;
        v.value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector2& Vector2::operator *=(const Vector2 &rhs)
    {
        value = _mm_mul_ps(value, rhs.value);
        return *this;
    }

    Vector2& Vector2::operator *=(float rhs)
    {
        value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector2 Vector2::operator /(const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_div_ps(value, rhs.value);
        return v;
    }

    Vector2 Vector2::operator /(float rhs)
    {
        Vector2 v;
        v.value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector2& Vector2::operator /=(const Vector2 &rhs)
    {
        value = _mm_div_ps(value, rhs.value);
        return *this;
    }

    Vector2& Vector2::operator /=(float rhs)
    {
        value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    bool Vector2::operator ==(const Vector2 &rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    bool Vector2::operator !=(const Vector2 &rhs)
    {
        return x != rhs.x || y != rhs.y;
    }

    Vector2 operator +(float lhs, const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_add_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector2 operator -(float lhs, const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_sub_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector2 operator *(float lhs, const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_mul_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector2 operator /(float lhs, const Vector2 &rhs)
    {
        Vector2 v;
        v.value = _mm_div_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }    
};