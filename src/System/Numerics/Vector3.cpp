#include "Vector3.hpp"

namespace Gravy::System::Numerics
{
    glm::vec3 Vector3f::UnitX()
    {
        return glm::vec3(1.0f, 0.0f, 0.0f);
    }

    glm::vec3 Vector3f::UnitY()
    {
        return glm::vec3(0.0f, 1.0f, 0.0f);
    }

    glm::vec3 Vector3f::UnitZ()
    {
        return glm::vec3(0.0f, 0.0f, 1.0f);
    }

    glm::vec3 Vector3f::Cross(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::cross(v1, v2);
    }

    float Vector3f::Dot(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::dot(v1, v2);
    }

    float Vector3f::Distance(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::distance(v1, v2);
    }

    float Vector3f::DistanceSquared(const glm::vec3 &v1, const glm::vec3 &v2)
    {
        return glm::distance2(v1, v2);
    }

    float Vector3f::Length(const glm::vec3 &v)
    {
        return glm::length(v);
    }

    float Vector3f::LengthSquared(const glm::vec3 &v)
    {
        return glm::length2(v);
    }

    glm::vec3 Vector3f::Lerp(const glm::vec3 &v1, const glm::vec3 &v2, float t)
    {
        return glm::lerp(v1, v2, t);
    }

    glm::vec3 Vector3f::Normalize(const glm::vec3 &v)
    {
        return glm::normalize(v);
    }

    glm::vec3 Vector3f::TransformVector(const glm::vec3 &v, const glm::mat4 &m)
    {
        glm::vec4 homogenousVec(v, 1.0f);
        glm::vec4 transformedVec = m * homogenousVec;
        return glm::vec3(transformedVec);
    }
};