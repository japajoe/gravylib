#ifndef GRAVY_MATRIX4_HPP
#define GRAVY_MATRIX4_HPP

#include "Vector3.hpp"
#include "Vector4.hpp"

namespace Gravy::System::Numerics
{
    class Matrix4
    {
    public:
        union
		{
			Vector4 columns[4];
			struct
			{
				float m11, m21, m31, m41;
				float m12, m22, m32, m42;
				float m13, m23, m33, m43;
				float m14, m24, m34, m44;
			};
			float m[4][4];
		};

        Matrix4();
        void Invert();
        Matrix4 Inverse() const;
        static Matrix4 GetIdentity();
        static Matrix4 CreateRotationX(float angleRad);
        static Matrix4 CreateRotationY(float angleRad);
        static Matrix4 CreateRotationZ(float angleRad);
        static Matrix4 CreateRotation(float angleRadX, float angleRadY, float angleRadZ);
        static Matrix4 CreateTranslation(float x, float y, float z);
        static Matrix4 CreateScale(float x, float y, float z);
        static Matrix4 Perspective(float fovDegrees, float aspectRatio, float near, float far);

        Matrix4 operator*(const Matrix4 &rhs) const;
        Vector4 operator*(const Vector4 &rhs) const;
    };
};

#endif