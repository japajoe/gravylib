#include "Vector4.hpp"
#include <cmath>

namespace Gravy::System::Numerics
{
    Vector4::Vector4()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }
    
    Vector4::Vector4(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->z = w;
    }

    float Vector4::Magnitude()
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    void Vector4::Normalize()
    {
        float scale = 1.0f / Magnitude();
        value = _mm_mul_ps(value, _mm_set_ps1(scale));
    }

    Vector4 Vector4::Normalize(const Vector4 &v)
    {
        Vector4 normalized = v;
        float scale = 1.0f / normalized.Magnitude();
        normalized.value = _mm_mul_ps(normalized.value, _mm_set_ps1(scale));
        return normalized;
    }

    float Vector4::Dot(const Vector4 &lhs, const Vector4 &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

    Vector4 Vector4::Lerp(const Vector4 &a, const Vector4 &b, float t)
    {
        Vector4 c;
        c.x = t * (b.x - a.x) + a.x;
        c.y = t * (b.y - a.y) + a.y;
        c.z = t * (b.z - a.z) + a.z;
        c.w = t * (b.w - a.w) + a.w;
        return c;
    }

    Vector4 Vector4::operator +(const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_add_ps(value, rhs.value);
        return v;
    }

    Vector4 Vector4::operator +(float rhs)
    {
        Vector4 v;
        v.value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector4& Vector4::operator +=(const Vector4 &rhs)
    {
        value = _mm_add_ps(value, rhs.value);
        return *this;
    }

    Vector4& Vector4::operator +=(float rhs)
    {
        value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector4 Vector4::operator -(const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_sub_ps(value, rhs.value);
        return v;
    }

    Vector4 Vector4::operator -(float rhs)
    {
        Vector4 v;
        v.value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector4& Vector4::operator -=(const Vector4 &rhs)
    {
        value = _mm_sub_ps(value, rhs.value);
        return *this;
    }

    Vector4& Vector4::operator -=(float rhs)
    {
        value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector4 Vector4::operator *(const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_mul_ps(value, rhs.value);
        return v;
    }

    Vector4 Vector4::operator *(float rhs)
    {
        Vector4 v;
        v.value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector4& Vector4::operator *=(const Vector4 &rhs)
    {
        value = _mm_mul_ps(value, rhs.value);
        return *this;
    }

    Vector4& Vector4::operator *=(float rhs)
    {
        value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector4 Vector4::operator /(const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_div_ps(value, rhs.value);
        return v;
    }

    Vector4 Vector4::operator /(float rhs)
    {
        Vector4 v;
        v.value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector4& Vector4::operator /=(const Vector4 &rhs)
    {
        value = _mm_div_ps(value, rhs.value);
        return *this;
    }

    Vector4& Vector4::operator /=(float rhs)
    {
        value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    bool Vector4::operator ==(const Vector4 &rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    bool Vector4::operator !=(const Vector4 &rhs)
    {
        return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
    }

    Vector4 operator +(float lhs, const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_add_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector4 operator -(float lhs, const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_sub_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector4 operator *(float lhs, const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_mul_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector4 operator /(float lhs, const Vector4 &rhs)
    {
        Vector4 v;
        v.value = _mm_div_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }
};