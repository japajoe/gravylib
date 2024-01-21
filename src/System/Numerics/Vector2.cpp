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
        x *= scale;
        y *= scale;
    }

    Vector2 Vector2::Normalize(const Vector2 &v)
    {
        Vector2 normalized = v;
        float scale = 1.0f / normalized.Magnitude();
        normalized.x *= scale;
        normalized.y *= scale;
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
        return Vector2(x + rhs.x, y + rhs.y);
    }

    Vector2 Vector2::operator +(float rhs)
    {
        return Vector2(x + rhs, y + rhs);
    }

    Vector2& Vector2::operator +=(const Vector2 &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vector2& Vector2::operator +=(float rhs)
    {
        x += rhs;
        y += rhs;
        return *this;
    }

    Vector2 Vector2::operator -(const Vector2 &rhs)
    {
        return Vector2(x - rhs.x, y - rhs.y);
    }

    Vector2 Vector2::operator -(float rhs)
    {
        return Vector2(x - rhs, y - rhs);
    }

    Vector2& Vector2::operator -=(const Vector2 &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vector2& Vector2::operator -=(float rhs)
    {
        x -= rhs;
        y -= rhs;
        return *this;
    }

    Vector2 Vector2::operator *(const Vector2 &rhs)
    {
        return Vector2(x * rhs.x, y * rhs.y);
    }

    Vector2 Vector2::operator *(float rhs)
    {
        return Vector2(x * rhs, y * rhs);
    }

    Vector2& Vector2::operator *=(const Vector2 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector2& Vector2::operator *=(float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Vector2 Vector2::operator /(const Vector2 &rhs)
    {
        return Vector2(x / rhs.x, y / rhs.y);
    }

    Vector2 Vector2::operator /(float rhs)
    {
        return Vector2(x / rhs, y / rhs);
    }

    Vector2& Vector2::operator /=(const Vector2 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vector2& Vector2::operator /=(float rhs)
    {
        x /= rhs;
        y /= rhs;
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
        return Vector2(lhs + rhs.x, lhs + rhs.y);
    }

    Vector2 operator -(float lhs, const Vector2 &rhs)
    {
        return Vector2(lhs - rhs.x, lhs - rhs.y);
    }

    Vector2 operator *(float lhs, const Vector2 &rhs)
    {
        return Vector2(lhs * rhs.x, lhs * rhs.y);
    }

    Vector2 operator /(float lhs, const Vector2 &rhs)
    {
        return Vector2(lhs / rhs.x, lhs / rhs.y);
    }    
};