#ifndef GRAVY_QUATERNION_HPP
#define GRAVY_QUATERNION_HPP

#include "../../External/glm/glm.hpp"
#include "../../External/glm/gtc/quaternion.hpp"
#include "../../External/glm/gtc/matrix_inverse.hpp"
#include "../../External/glm/gtc/matrix_transform.hpp"
#include "../../External/glm/gtx/quaternion.hpp"
#include "../../External/glm/gtx/transform.hpp"
#include "../../External/glm/gtx/compatibility.hpp"
#include "../../External/glm/gtx/euler_angles.hpp"

namespace Gravy::System::Numerics
{
    typedef glm::quat Quaternion;

    class Quaternionf
    {
    public:
        static glm::quat Euler(float x, float y, float z);
        static glm::quat FromAxisAngle(const glm::vec3 &axis, float angle);
        static glm::quat Invert(const glm::quat &v);
        static float Length(const glm::quat &v);
        static float LengthSquared(const glm::quat &v);
        static glm::quat Normalize(const glm::quat &v);
        static glm::quat Slerp(const glm::quat &v1, const glm::quat &v2, float t);
        static glm::vec3 ToEulerAngles(const glm::quat &v);
    };
};

#endif