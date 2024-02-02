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
        static glm::vec3 UnitX();
        static glm::vec3 UnitY();
        static glm::vec3 UnitZ();
        static glm::vec3 Cross(const glm::vec3 &v1, const glm::vec3 &v2);
        static float Dot(const glm::vec3 &v1, const glm::vec3 &v2);
        static float Distance(const glm::vec3 &v1, const glm::vec3 &v2);
        static float DistanceSquared(const glm::vec3 &v1, const glm::vec3 &v2);
        static float Length(const glm::vec3 &v);
        static float LengthSquared(const glm::vec3 &v);
        static glm::vec3 Lerp(const glm::vec3 &v1, const glm::vec3 &v2, float t);
        static glm::vec3 Normalize(const glm::vec3 &v);
        static glm::vec3 TransformVector(const glm::vec3 &v, const glm::mat4 &m);
    };
};

#endif