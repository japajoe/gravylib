#include "Matrix4.hpp"

namespace Gravy::System::Numerics
{
    glm::mat4 Matrix4f::GetIdentity()
    {
        return glm::mat4();
    }

    glm::mat4 Matrix4f::Perspective(float fovDegrees, float aspectRatio, float near, float far)
    {
        return glm::perspective(glm::radians(fovDegrees), aspectRatio, near, far);
    }

    glm::mat4 Matrix4f::Orthographic(float left, float right, float bottom, float top, float near, float far)
    {
        if(near > 0 && far > 0)
            return glm::ortho(left, right, bottom, top, near, far);
        else
            return glm::ortho(left, right, bottom, top);
    }

    glm::mat4 Matrix4f::CreateTranslation(float x, float y, float z)
    {
        return glm::translate(glm::vec3(x, y, z));
    }

    glm::mat4 Matrix4f::CreateRotation(float x, float y, float z)
    {
        return glm::eulerAngleXYZ(x, y, z);
    }

    glm::mat4 Matrix4f::CreateRotation(float x, float y, float z, float w)
    {
        return glm::toMat4(glm::quat(w, x, y, z));
    }

    glm::mat4 Matrix4f::CreateRotationX(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::mat4 Matrix4f::CreateRotationY(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::mat4 Matrix4f::CreateRotationZ(float angle)
    {
        return glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    glm::mat4 Matrix4f::CreateScale(float x, float y, float z)
    {
        return glm::scale(glm::vec3(x, y, z));
    }

    glm::quat Matrix4f::ExtractRotation(const glm::mat4 &v)
    {
        glm::vec3 pos = v[3];
        glm::vec3 scale;
        for(int i = 0; i < 3; i++)
            scale[i] = glm::length(glm::vec3(v[i]));
        const glm::mat3 rotMtx(
            glm::vec3(v[0]) / scale[0],
            glm::vec3(v[1]) / scale[1],
            glm::vec3(v[2]) / scale[2]);
        glm::quat rot = glm::quat_cast(rotMtx);
        return rot;
    }

    glm::vec3 Matrix4f::ExtractScale(const glm::mat4 &v)
    {
        glm::vec3 scale;
        for(int i = 0; i < 3; i++)
            scale[i] = glm::length(glm::vec3(v[i]));
        return scale;
    }

    glm::vec3 Matrix4f::ExtractTranslation(const glm::mat4 &v)
    {
        glm::vec3 pos = v[3];
        return pos;
    }

    glm::mat4 Matrix4f::Invert(const glm::mat4 &v)
    {
        return glm::inverse(v);
    }
};