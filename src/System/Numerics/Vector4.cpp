#include "Vector4.hpp"

namespace Gravy::System::Numerics
{
    float Vector4f::Dot(const Vector4 &v1, const Vector4 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector4f::Distance(const Vector4 &v1, const Vector4 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector4f::DistanceSquared(const Vector4 &v1, const Vector4 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector4f::Length(const Vector4 &v)
    {
        return glm::length(v);
    }

    float Vector4f::LengthSquared(const Vector4 &v)
    {
        return glm::length2(v);
    }

    Vector4 Vector4f::Lerp(const Vector4 &v1, const Vector4 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    Vector4 Vector4f::Normalize(const Vector4 &v)
    {
        return glm::normalize(v);
    }
};