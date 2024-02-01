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
        static float Dot(const Vector2 &v1, const Vector2 &v2);
        static float Distance(const Vector2 &v1, const Vector2 &v2);
        static float DistanceSquared(const Vector2 &v1, const Vector2 &v2);
        static float Length(const Vector2 &v);
        static float LengthSquared(const Vector2 &v);
        static Vector2 Lerp(const Vector2 &v1, const Vector2 &v2, float t);
        static Vector2 Normalize(const Vector2 &v);
    };
};

#endif