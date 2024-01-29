#include "Vector3.hpp"
#include <cmath>

namespace Gravy::System::Numerics
{
    Vector3::Vector3()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }
    
    Vector3::Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float Vector3::Magnitude()
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    void Vector3::Normalize()
    {
        float scale = 1.0f / Magnitude();
        value = _mm_mul_ps(value, _mm_set_ps1(scale));
    }

    Vector3 Vector3::Normalize(const Vector3 &v)
    {
        Vector3 normalized = v;
        float scale = 1.0f / normalized.Magnitude();
        normalized.value = _mm_mul_ps(normalized.value, _mm_set_ps1(scale));
        return normalized;
    }

    float Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs)
    {
        return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x);
    }

    Vector3 Vector3::Lerp(const Vector3 &a, const Vector3 &b, float t)
    {
        Vector3 c;
        c.x = t * (b.x - a.x) + a.x;
        c.y = t * (b.y - a.y) + a.y;
        c.z = t * (b.z - a.z) + a.z;
        return c;
    }

    Vector3 Vector3::operator +(const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_add_ps(value, rhs.value);
        return v;
    }

    Vector3 Vector3::operator +(float rhs)
    {
        Vector3 v;
        v.value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector3& Vector3::operator +=(const Vector3 &rhs)
    {
        value = _mm_add_ps(value, rhs.value);
        return *this;
    }

    Vector3& Vector3::operator +=(float rhs)
    {
        value = _mm_add_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector3 Vector3::operator -(const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_sub_ps(value, rhs.value);
        return v;
    }

    Vector3 Vector3::operator -(float rhs)
    {
        Vector3 v;
        v.value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector3& Vector3::operator -=(const Vector3 &rhs)
    {
        value = _mm_sub_ps(value, rhs.value);
        return *this;
    }

    Vector3& Vector3::operator -=(float rhs)
    {
        value = _mm_sub_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector3 Vector3::operator *(const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_mul_ps(value, rhs.value);
        return v;
    }

    Vector3 Vector3::operator *(float rhs)
    {
        Vector3 v;
        v.value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector3& Vector3::operator *=(const Vector3 &rhs)
    {
        value = _mm_mul_ps(value, rhs.value);
        return *this;
    }

    Vector3& Vector3::operator *=(float rhs)
    {
        value = _mm_mul_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    Vector3 Vector3::operator /(const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_div_ps(value, rhs.value);
        return v;
    }

    Vector3 Vector3::operator /(float rhs)
    {
        Vector3 v;
        v.value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return v;
    }

    Vector3& Vector3::operator /=(const Vector3 &rhs)
    {
        value = _mm_div_ps(value, rhs.value);
        return *this;
    }

    Vector3& Vector3::operator /=(float rhs)
    {
        value = _mm_div_ps(value, _mm_set_ps1(rhs));
        return *this;
    }

    bool Vector3::operator ==(const Vector3 &rhs)
    {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool Vector3::operator !=(const Vector3 &rhs)
    {
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    Vector3 operator +(float lhs, const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_add_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector3 operator -(float lhs, const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_sub_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector3 operator *(float lhs, const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_mul_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }

    Vector3 operator /(float lhs, const Vector3 &rhs)
    {
        Vector3 v;
        v.value = _mm_div_ps(_mm_set_ps1(lhs), rhs.value);
        return v;
    }
};