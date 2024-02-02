#include "Vector4.hpp"

namespace Gravy::System::Numerics
{
    float Vector4f::Dot(const glm::vec4 &v1, const glm::vec4 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector4f::Distance(const glm::vec4 &v1, const glm::vec4 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector4f::DistanceSquared(const glm::vec4 &v1, const glm::vec4 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector4f::Length(const glm::vec4 &v)
    {
        return glm::length(v);
    }

    float Vector4f::LengthSquared(const glm::vec4 &v)
    {
        return glm::length2(v);
    }

    glm::vec4 Vector4f::Lerp(const glm::vec4 &v1, const glm::vec4 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    glm::vec4 Vector4f::Normalize(const glm::vec4 &v)
    {
        return glm::normalize(v);
    }
};