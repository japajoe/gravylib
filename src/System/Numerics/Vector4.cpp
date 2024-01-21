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
        x *= scale;
        y *= scale;
        z *= scale;
        w *= scale;
    }

    Vector4 Vector4::Normalize(const Vector4 &v)
    {
        Vector4 normalized = v;
        float scale = 1.0f / normalized.Magnitude();
        normalized.x *= scale;
        normalized.y *= scale;
        normalized.z *= scale;
        normalized.w *= scale;
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
        return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
    }

    Vector4 Vector4::operator +(float rhs)
    {
        return Vector4(x + rhs, y + rhs, z + rhs, w + rhs);
    }

    Vector4& Vector4::operator +=(const Vector4 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vector4& Vector4::operator +=(float rhs)
    {
        x += rhs;
        y += rhs;
        z += rhs;
        w += rhs;
        return *this;
    }

    Vector4 Vector4::operator -(const Vector4 &rhs)
    {
        return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
    }

    Vector4 Vector4::operator -(float rhs)
    {
        return Vector4(x - rhs, y - rhs, z - rhs, w - rhs);
    }

    Vector4& Vector4::operator -=(const Vector4 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vector4& Vector4::operator -=(float rhs)
    {
        x -= rhs;
        y -= rhs;
        z -= rhs;
        w -= rhs;
        return *this;
    }

    Vector4 Vector4::operator *(const Vector4 &rhs)
    {
        return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
    }

    Vector4 Vector4::operator *(float rhs)
    {
        return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
    }

    Vector4& Vector4::operator *=(const Vector4 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
    }

    Vector4& Vector4::operator *=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        w *= rhs;
        return *this;
    }

    Vector4 Vector4::operator /(const Vector4 &rhs)
    {
        return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
    }

    Vector4 Vector4::operator /(float rhs)
    {
        return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
    }

    Vector4& Vector4::operator /=(const Vector4 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    Vector4& Vector4::operator /=(float rhs)
    {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        w /= rhs;
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
        return Vector4(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z, lhs + rhs.w);
    }

    Vector4 operator -(float lhs, const Vector4 &rhs)
    {
        return Vector4(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z, lhs - rhs.w);
    }

    Vector4 operator *(float lhs, const Vector4 &rhs)
    {
        return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
    }

    Vector4 operator /(float lhs, const Vector4 &rhs)
    {
        return Vector4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
    }
};