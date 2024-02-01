#ifndef GRAVY_VECTOR4_HPP
#define GRAVY_VECTOR4_HPP

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
    typedef glm::vec4 Vector4;

    class Vector4f
    {
    public:
        static float Dot(const Vector4 &v1, const Vector4 &v2);
        static float Distance(const Vector4 &v1, const Vector4 &v2);
        static float DistanceSquared(const Vector4 &v1, const Vector4 &v2);
        static float Length(const Vector4 &v);
        static float LengthSquared(const Vector4 &v);
        static Vector4 Lerp(const Vector4 &v1, const Vector4 &v2, float t);
        static Vector4 Normalize(const Vector4 &v);
    };
};

#endif