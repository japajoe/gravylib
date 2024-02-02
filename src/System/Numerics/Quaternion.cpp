#include "Quaternion.hpp"

namespace Gravy::System::Numerics
{
    glm::quat Quaternionf::Euler(float x, float y, float z)
    {
        return glm::quat(glm::vec3(x, y, z));
    }

    glm::quat Quaternionf::FromAxisAngle(const glm::vec3 &axis, float angle)
    {
        return glm::angleAxis(angle, axis);
    }

    glm::quat Quaternionf::Invert(const glm::quat &v)
    {
        return glm::inverse(v);
    }

    float Quaternionf::Length(const glm::quat &v)
    {
        return glm::length(v);
    }

    float Quaternionf::LengthSquared(const glm::quat &v)
    {
        return glm::length2(v);
    }

    glm::quat Quaternionf::Normalize(const glm::quat &v)
    {
        return glm::normalize(v);
    }

    glm::quat Quaternionf::Slerp(const glm::quat &v1, const glm::quat &v2, float t)
    {
        return glm::slerp(v1, v2, t);
    }

    glm::vec3 Quaternionf::ToEulerAngles(const glm::quat &v)
    {
        return glm::eulerAngles(v);
    }
};