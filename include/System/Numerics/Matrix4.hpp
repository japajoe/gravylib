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
#include "../../External/glm/gtx/matrix_decompose.hpp"

namespace Gravy::System::Numerics
{
    typedef glm::mat4 Matrix4;

    class Matrix4f
    {
    public:
        static glm::mat4 GetIdentity();
        static glm::mat4 Perspective(float fovDegrees, float aspectRatio, float near, float far);
        static glm::mat4 Orthographic(float left, float right, float bottom, float top, float near = 0, float far = 0);
        static glm::mat4 CreateTranslation(float x, float y, float z);
        static glm::mat4 CreateRotation(float x, float y, float z);
        static glm::mat4 CreateRotation(float x, float y, float z, float w);
        static glm::mat4 CreateRotationX(float angle);
        static glm::mat4 CreateRotationY(float angle);
        static glm::mat4 CreateRotationZ(float angle);
        static glm::mat4 CreateScale(float x, float y, float z);
        static glm::quat ExtractRotation(const glm::mat4 &v);
        static glm::vec3 ExtractScale(const glm::mat4 &v);
        static glm::vec3 ExtractTranslation(const glm::mat4 &v);
        static glm::mat4 Invert(const glm::mat4 &v);
    };
};

#endif