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
#include "Vector3.hpp"

namespace Gravy::System::Numerics
{
    typedef glm::quat Quaternion;

    class Quaternionf
    {
        static Quaternion Euler(float x, float y, float z);
        static Quaternion FromAxisAngle(const Vector3 &axis, float angle);
        static float Length(const Quaternion &v);
        static float LengthSquared(const Quaternion &v);
        static Quaternion Normalize(const Quaternion &v);
        static Quaternion Slerp(const Quaternion &v1, const Quaternion &v2, float t);
        static Vector3 ToEulerAngles(const Quaternion &v);
    };
};

#endif