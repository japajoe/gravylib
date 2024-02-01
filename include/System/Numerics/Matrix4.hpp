#ifndef GRAVY_MATRIX4_HPP
#define GRAVY_MATRIX4_HPP

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
    typedef glm::mat4 Matrix4;

    class Matrix4f
    {
    public:
        static Matrix4 GetIdentity();
        static Matrix4 Perspective(float fovDegrees, float aspectRatio, float near, float far);
        static Matrix4 Orthographic(float left, float right, float bottom, float top, float near = 0, float far = 0);
        static Matrix4 CreateTranslation(float x, float y, float z);
        static Matrix4 CreateRotation(float x, float y, float z);
        static Matrix4 CreateRotation(float x, float y, float z, float w);
        static Matrix4 CreateRotationX(float angle);
        static Matrix4 CreateRotationY(float angle);
        static Matrix4 CreateRotationZ(float angle);
        static Matrix4 CreateScale(float x, float y, float z);
    };
};

#endif