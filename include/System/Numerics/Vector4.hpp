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
        static float Dot(const glm::vec4 &v1, const glm::vec4 &v2);
        static float Distance(const glm::vec4 &v1, const glm::vec4 &v2);
        static float DistanceSquared(const glm::vec4 &v1, const glm::vec4 &v2);
        static float Length(const glm::vec4 &v);
        static float LengthSquared(const glm::vec4 &v);
        static glm::vec4 Lerp(const glm::vec4 &v1, const glm::vec4 &v2, float t);
        static glm::vec4 Normalize(const glm::vec4 &v);
    };
};

#endif