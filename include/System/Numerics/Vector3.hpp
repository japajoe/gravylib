#ifndef GRAVY_VECTOR3_HPP
#define GRAVY_VECTOR3_HPP

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
    typedef glm::vec3 Vector3;

    class Vector3f
    {
    public:
        static Vector3 Cross(const Vector3 &v1, const Vector3 &v2);
        static float Dot(const Vector3 &v1, const Vector3 &v2);
        static float Distance(const Vector3 &v1, const Vector3 &v2);
        static float DistanceSquared(const Vector3 &v1, const Vector3 &v2);
        static float Length(const Vector3 &v);
        static float LengthSquared(const Vector3 &v);
        static Vector3 Lerp(const Vector3 &v1, const Vector3 &v2, float t);
        static Vector3 Normalize(const Vector3 &v);
    };
};

#endif