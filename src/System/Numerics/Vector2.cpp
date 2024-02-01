#include "Vector2.hpp"

namespace Gravy::System::Numerics
{
    float Vector2f::Dot(const Vector2 &v1, const Vector2 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector2f::Distance(const Vector2 &v1, const Vector2 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector2f::DistanceSquared(const Vector2 &v1, const Vector2 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector2f::Length(const Vector2 &v)
    {
        return glm::length(v);
    }

    float Vector2f::LengthSquared(const Vector2 &v)
    {
        return glm::length2(v);
    }

    Vector2 Vector2f::Lerp(const Vector2 &v1, const Vector2 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    Vector2 Vector2f::Normalize(const Vector2 &v)
    {
        return glm::normalize(v);
    }
};