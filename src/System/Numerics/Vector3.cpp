#include "Vector3.hpp"

namespace Gravy::System::Numerics
{
    Vector3 Vector3f::Cross(const Vector3 &v1, const Vector3 &v2)
    {
        return glm::cross(v1, v2);
    }

    float Vector3f::Dot(const Vector3 &v1, const Vector3 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector3f::Distance(const Vector3 &v1, const Vector3 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector3f::DistanceSquared(const Vector3 &v1, const Vector3 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector3f::Length(const Vector3 &v)
    {
        return glm::length(v);
    }

    float Vector3f::LengthSquared(const Vector3 &v)
    {
        return glm::length2(v);
    }

    Vector3 Vector3f::Lerp(const Vector3 &v1, const Vector3 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    Vector3 Vector3f::Normalize(const Vector3 &v)
    {
        return glm::normalize(v);
    }
};