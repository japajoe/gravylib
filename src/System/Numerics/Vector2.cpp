#include "Vector2.hpp"

namespace Gravy::System::Numerics
{
    float Vector2f::Dot(const glm::vec2 &v1, const glm::vec2 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector2f::Distance(const glm::vec2 &v1, const glm::vec2 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector2f::DistanceSquared(const glm::vec2 &v1, const glm::vec2 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector2f::Length(const glm::vec2 &v)
    {
        return glm::length(v);
    }

    float Vector2f::LengthSquared(const glm::vec2 &v)
    {
        return glm::length2(v);
    }

    glm::vec2 Vector2f::Lerp(const glm::vec2 &v1, const glm::vec2 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    glm::vec2 Vector2f::Normalize(const glm::vec2 &v)
    {
        return glm::normalize(v);
    }
};