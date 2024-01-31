#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Quaternion.hpp"
#include <cmath>
#include <algorithm>
#include <cstring>

namespace Gravy::System::Numerics
{
    Matrix4::Matrix4()
    {
        std::memset(m, 0, 16 * sizeof(float));
    }

	void Matrix4::Invert()
	{
		Matrix4 inverted = Inverse();
		*this = inverted;
	}

    Matrix4 Matrix4::Inverse() const
    {
        float det = m[0][0] * (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] - m[1][3] * m[2][2] * m[3][1]) -
                    m[0][1] * (m[1][0] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][2] - m[1][0] * m[2][3] * m[3][2] - m[1][2] * m[2][0] * m[3][3] - m[1][3] * m[2][2] * m[3][0]) +
                    m[0][2] * (m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] - m[1][3] * m[2][1] * m[3][0]) -
                    m[0][3] * (m[1][0] * m[2][1] * m[3][2] + m[1][1] * m[2][2] * m[3][0] + m[1][2] * m[2][0] * m[3][1] - m[1][0] * m[2][2] * m[3][1] - m[1][1] * m[2][0] * m[3][2] - m[1][2] * m[2][1] * m[3][0]);

        if (det == 0) 
        {
            // Matrix is singular, cannot compute inverse
            return *this;
        }

        float invDet = 1.0f / det;

        Matrix4 inverse;
        inverse.m[0][0] = (m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] - m[1][3] * m[2][2] * m[3][1]) * invDet;
        inverse.m[0][1] = (m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] + m[0][3] * m[2][2] * m[3][1] - m[0][1] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2]) * invDet;
        inverse.m[0][2] = (m[0][1] * m[1][2] * m[3][3] + m[0][2] * m[1][3] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] - m[0][3] * m[1][2] * m[3][1]) * invDet;
        inverse.m[0][3] = (m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] + m[0][3] * m[1][2] * m[2][1] - m[0][1] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2]) * invDet;
        inverse.m[1][0] = (m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] + m[1][3] * m[2][2] * m[3][0] - m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2]) * invDet;
        inverse.m[1][1] = (m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] - m[0][3] * m[2][2] * m[3][0]) * invDet;
        inverse.m[1][2] = (m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] + m[0][3] * m[1][2] * m[3][0] - m[0][0] * m[1][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2]) * invDet;
        inverse.m[1][3] = (m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] - m[0][3] * m[1][2] * m[2][0]) * invDet;
        inverse.m[2][0] = (m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] - m[1][3] * m[2][1] * m[3][0]) * invDet;
        inverse.m[2][1] = (m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] + m[0][3] * m[2][1] * m[3][0] - m[0][0] * m[2][1] * m[3][3] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1]) * invDet;
        inverse.m[2][2] = (m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] - m[0][3] * m[1][1] * m[3][0]) * invDet;
        inverse.m[2][3] = (m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] + m[0][3] * m[1][1] * m[2][0] - m[0][0] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1]) * invDet;
        inverse.m[3][0] = (m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] + m[1][2] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1]) * invDet;
        inverse.m[3][1] = (m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] - m[0][2] * m[2][1] * m[3][0]) * invDet;
        inverse.m[3][2] = (m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] + m[0][2] * m[1][1] * m[3][0] - m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1]) * invDet;
        inverse.m[3][3] = (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0]) * invDet;

        return inverse;
    }

	//Not tested yet
	Vector3 Matrix4::ExtractScale() const
	{
		float x = std::sqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
        float y = std::sqrt(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
        float z = std::sqrt(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]);
		return Vector3(x, y, z);
	}

	//Not tested yet
	Vector3 Matrix4::ExtractTranslation() const
	{
        float x = m[0][3];
        float y = m[1][3];
        float z = m[2][3];
		return Vector3(x, y, z);
	}

	//Not tested yet
    Quaternion Matrix4::ExtractRotation() const
	{
        Quaternion quaternion;

        float trace = m[0][0] + m[1][1] + m[2][2];
        if (trace > 0.0f) 
		{
            float S = sqrt(trace + 1.0f) * 2.0f;
            quaternion.w = 0.25f * S;
            quaternion.x = (m[2][1] - m[1][2]) / S;
            quaternion.y = (m[0][2] - m[2][0]) / S;
            quaternion.z = (m[1][0] - m[0][1]) / S;
        }
		else if ((m[0][0] > m[1][1]) && (m[0][0] > m[2][2])) 
		{
            float S = sqrt(1.0f + m[0][0] - m[1][1] - m[2][2]) * 2.0f;
            quaternion.w = (m[2][1] - m[1][2]) / S;
            quaternion.x = 0.25f * S;
            quaternion.y = (m[0][1] + m[1][0]) / S;
            quaternion.z = (m[0][2] + m[2][0]) / S;
        }
		else if (m[1][1] > m[2][2]) 
		{
            float S = sqrt(1.0f + m[1][1] - m[0][0] - m[2][2]) * 2.0f;
            quaternion.w = (m[0][2] - m[2][0]) / S;
            quaternion.x = (m[0][1] + m[1][0]) / S;
            quaternion.y = 0.25f * S;
            quaternion.z = (m[1][2] + m[2][1]) / S;
        }
		else
		{
            float S = sqrt(1.0f + m[2][2] - m[0][0] - m[1][1]) * 2.0f;
            quaternion.w = (m[1][0] - m[0][1]) / S;
            quaternion.x = (m[0][2] + m[2][0]) / S;
            quaternion.y = (m[1][2] + m[2][1]) / S;
            quaternion.z = 0.25f * S;
        }

        return quaternion;
    }

	Matrix4 Matrix4::GetIdentity()
	{
		Matrix4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Matrix4 Matrix4::CreateRotationX(float angleRad)
	{
		Matrix4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = cosf(angleRad);
		matrix.m[1][2] = sinf(angleRad);
		matrix.m[2][1] = -sinf(angleRad);
		matrix.m[2][2] = cosf(angleRad);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Matrix4 Matrix4::CreateRotationY(float angleRad)
	{
		Matrix4 matrix;
		matrix.m[0][0] = cosf(angleRad);
		matrix.m[0][2] = sinf(angleRad);
		matrix.m[2][0] = -sinf(angleRad);
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = cosf(angleRad);
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

	Matrix4 Matrix4::CreateRotationZ(float angleRad)
	{
		Matrix4 matrix;
		matrix.m[0][0] = cosf(angleRad);
		matrix.m[0][1] = sinf(angleRad);
		matrix.m[1][0] = -sinf(angleRad);
		matrix.m[1][1] = cosf(angleRad);
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		return matrix;
	}

    Matrix4 Matrix4::CreateRotation(float angleRadX, float angleRadY, float angleRadZ)
    {
        Matrix4 rotX = CreateRotationX(angleRadX);
        Matrix4 rotY = CreateRotationY(angleRadY);
        Matrix4 rotZ = CreateRotationZ(angleRadZ);
        Matrix4 rotation = rotZ * rotY * rotX;
        return rotation;
    }

	Matrix4 Matrix4::CreateTranslation(float x, float y, float z)
	{
		Matrix4 matrix;
		matrix.m[0][0] = 1.0f;
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = 1.0f;
		matrix.m[3][3] = 1.0f;
		matrix.m[3][0] = x;
		matrix.m[3][1] = y;
		matrix.m[3][2] = z;
		return matrix;
	}

    Matrix4 Matrix4::CreateScale(float x, float y, float z)
    {
        Matrix4 matrix;
        matrix.m[0][0] = x; 
        matrix.m[1][1] = y; 
        matrix.m[2][2] = z; 
        matrix.m[3][3] = 1.0f;
        return matrix;
    }

	Matrix4 Matrix4::Perspective(float fovDegrees, float aspectRatio, float near, float far)
	{
        float fov = (M_PI / 180.0) * fovDegrees;
        const float tanHalfFOV = tanf(fov / 2.0f);
        Matrix4 result;
        result.m[0][0] = 1.0f / (aspectRatio * tanHalfFOV);
        result.m[1][1] = 1.0f / (tanHalfFOV);
        result.m[2][2] = -(far + near) / (far - near);
        result.m[2][3] = -1.0f;
        result.m[3][2] = -(2.0f * far * near) / (far - near);
        return result;
	}

    Matrix4 Matrix4::operator*(const Matrix4 &rhs) const
    {
		Matrix4 matrix;
		for (int c = 0; c < 4; c++)
			for (int r = 0; r < 4; r++)
				matrix.m[r][c] = m[r][0] * rhs.m[0][c] + m[r][1] * rhs.m[1][c] + m[r][2] * rhs.m[2][c] + m[r][3] * rhs.m[3][c];
		return matrix;
    }

    Vector4 Matrix4::operator*(const Vector4 &rhs) const
    {
		Vector4 v;
		v.x = rhs.x * m[0][0] + rhs.y * m[1][0] + rhs.z * m[2][0] + rhs.w * m[3][0];
		v.y = rhs.x * m[0][1] + rhs.y * m[1][1] + rhs.z * m[2][1] + rhs.w * m[3][1];
		v.z = rhs.x * m[0][2] + rhs.y * m[1][2] + rhs.z * m[2][2] + rhs.w * m[3][2];
		v.w = rhs.x * m[0][3] + rhs.y * m[1][3] + rhs.z * m[2][3] + rhs.w * m[3][3];
		return v;
    }
}