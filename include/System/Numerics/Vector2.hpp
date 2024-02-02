#ifndef GRAVY_VECTOR2_HPP
#define GRAVY_VECTOR2_HPP

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
    typedef glm::vec2 Vector2;

    class Vector2f
    {
    public:
        static float Dot(const glm::vec2 &v1, const glm::vec2 &v2);
        static float Distance(const glm::vec2 &v1, const glm::vec2 &v2);
        static float DistanceSquared(const glm::vec2 &v1, const glm::vec2 &v2);
        static float Length(const glm::vec2 &v);
        static float LengthSquared(const glm::vec2 &v);
        static glm::vec2 Lerp(const glm::vec2 &v1, const glm::vec2 &v2, float t);
        static glm::vec2 Normalize(const glm::vec2 &v);
    };
};

#endif