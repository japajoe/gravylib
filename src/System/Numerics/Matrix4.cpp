#include "Matrix4.hpp"

namespace Gravy::System::Numerics
{
    Matrix4 Matrix4f::GetIdentity()
    {
        return glm::mat4();
    }

    Matrix4 Matrix4f::Perspective(float fovDegrees, float aspectRatio, float near, float far)
    {
        return glm::perspective(glm::radians(fovDegrees), aspectRatio, near, far);
    }

    Matrix4 Matrix4f::Orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        if(near > 0 && far > 0)
            return glm::ortho(left, right, bottom, top, near, far);
        else
            return glm::ortho(left, right, bottom, top);
    }

    Matrix4 Matrix4f::CreateTranslation(float x, float y, float z)
    {
        return glm::translate(glm::vec3(x, y, z));
    }

    Matrix4 Matrix4f::CreateRotation(float x, float y, float z)
    {
        return glm::eulerAngleXYZ(x, y, z);
    }

    Matrix4 Matrix4f::CreateRotation(float x, float y, float z, float w)
    {
        return glm::toMat4(glm::quat(w, x, y, z));
    }

    Matrix4 Matrix4f::CreateRotationX(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    Matrix4 Matrix4f::CreateRotationY(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    Matrix4 Matrix4f::CreateRotationZ(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    Matrix4 Matrix4f::CreateScale(float x, float y, float z)
    {
        return glm::scale(glm::vec3(x, y, z));
    }
};