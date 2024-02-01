#include "Quaternion.hpp"

namespace Gravy::System::Numerics
{
    Quaternion Quaternionf::Euler(float x, float y, float z)
    {
        return glm::quat(glm::vec3(x, y, z));
    }

    Quaternion Quaternionf::FromAxisAngle(const Vector3 &axis, float angle)
    {
        return glm::angleAxis(angle, axis);
    }

    float Quaternionf::Length(const Quaternion &v)
    {
        return glm::length(v);
    }

    float Quaternionf::LengthSquared(const Quaternion &v)
    {
        return glm::length2(v);
    }

    Quaternion Quaternionf::Normalize(const Quaternion &v)
    {
        return glm::normalize(v);
    }

    Quaternion Quaternionf::Slerp(const Quaternion &v1, const Quaternion &v2, float t)
    {
        return glm::slerp(v1, v2, t);
    }

    Vector3 Quaternionf::ToEulerAngles(const Quaternion &v)
    {
        return glm::eulerAngles(v);
    }
};