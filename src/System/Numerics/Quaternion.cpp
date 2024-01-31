/*
Copyright (c) 2006 - 2008 The Open Toolkit library.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include "Quaternion.hpp"
#include <cmath>

namespace Gravy::System::Numerics
{
    Quaternion::Quaternion()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 1;
    }
    
    Quaternion::Quaternion(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->z = w;
    }

    Quaternion::Quaternion(float rotationX, float rotationY, float rotationZ)
    {
        rotationX *= 0.5f;
        rotationY *= 0.5f;
        rotationZ *= 0.5f;

        float c1 = cos(rotationX);
        float c2 = cos(rotationY);
        float c3 = cos(rotationZ);
        float s1 = sin(rotationX);
        float s2 = sin(rotationY);
        float s3 = sin(rotationZ);

        this->w = (c1 * c2 * c3) - (s1 * s2 * s3);
        this->x = (s1 * c2 * c3) + (c1 * s2 * s3);
        this->y = (c1 * s2 * c3) - (s1 * c2 * s3);
        this->z = (c1 * c2 * s3) + (s1 * s2 * c3);
    }

    Quaternion::Quaternion(const Vector3 &v, float w)
    {
        this->xyz = v;
        this->w = w;
    }

    float Quaternion::Magnitude()
    {
        return std::sqrt((w * w) + xyz.LengthSquared());
    }

    float Quaternion::Length()
    {
        return std::sqrt((w * w) + xyz.LengthSquared());
    }

    float Quaternion::LengthSquared()
    {
        return (w * w) + xyz.LengthSquared();
    }

    Vector3 Quaternion::ToEulerAngles()
    {
        /*
        reference
        http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
        http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/
        */

        Quaternion q = *this;

        Vector3 eulerAngles;

        // Threshold for the singularities found at the north/south poles.
        const float SINGULARITY_THRESHOLD = 0.4999995f;

        float sqw = q.w * q.w;
        float sqx = q.x * q.x;
        float sqy = q.y * q.y;
        float sqz = q.z * q.z;
        float unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
        float singularityTest = (q.x * q.z) + (q.w * q.y);

        if (singularityTest > SINGULARITY_THRESHOLD * unit)
        {
            eulerAngles.z = 2 * atan2(q.x, q.w);
            eulerAngles.y = (M_PI / 2.0);
            eulerAngles.x = 0;
        }
        else if (singularityTest < -SINGULARITY_THRESHOLD * unit)
        {
            eulerAngles.z = -2 * atan2(q.x, q.w);
            eulerAngles.y = -(M_PI / 2.0);
            eulerAngles.x = 0;
        }
        else
        {
            eulerAngles.z = atan2(2 * ((q.w * q.z) - (q.x * q.y)), sqw + sqx - sqy - sqz);
            eulerAngles.y = asin(2 * singularityTest / unit);
            eulerAngles.x = atan2(2 * ((q.w * q.x) - (q.y * q.z)), sqw - sqx - sqy + sqz);
        }

        return eulerAngles;
    }

    Vector3 Quaternion::ToEulerAngles(const Quaternion &value)
    {
        Quaternion q = value;
        return q.ToEulerAngles();
    }

    void Quaternion::Normalize()
    {
        float scale = 1.0f / Length();
        xyz *= scale;
        w *= scale;
    }

    Quaternion Normalize(const Quaternion &value)
    {
        Quaternion q = value;
        float scale = 1.0f / q.Length();
        return Quaternion(q.xyz * scale, q.w * scale);
    }

    Quaternion Quaternion::GetIdentity()
    {
        return Quaternion(0, 0, 0, 1);
    }

    Quaternion Quaternion::Euler(float pitch, float yaw, float roll)
    {
        return Quaternion(pitch, yaw, roll);
    }

    Quaternion Quaternion::Euler(const Vector3 &eulerAngles)
    {
        return Quaternion(eulerAngles.x, eulerAngles.y, eulerAngles.z);
    }

    Quaternion Quaternion::FromAxisAngle(const Vector3 &axis, float angle)
    {
        Vector3 axs = axis;
        if (axs.LengthSquared() == 0.0f)
            return Quaternion::GetIdentity();

        Quaternion result = Quaternion::GetIdentity();

        angle *= 0.5f;
        axs.Normalize();
        result.xyz = axs * sin(angle);
        result.w = cos(angle);

        return Normalize(result);
    }

    Quaternion Quaternion::Slerp(const Quaternion &a, const Quaternion &b, float t)
    {
        Quaternion q1 = a;
        Quaternion q2 = b;

        // if either input is zero, return the other.
        if (q1.LengthSquared() == 0.0f)
        {
            if (q2.LengthSquared() == 0.0f)
            {
                return GetIdentity();
            }

            return q2;
        }

        if (q2.LengthSquared() == 0.0f)
        {
            return q1;
        }

        float cosHalfAngle = (q1.w * q2.w) + Vector3::Dot(q1.xyz, q2.xyz);

        if (cosHalfAngle >= 1.0f || cosHalfAngle <= -1.0f)
        {
            // angle = 0.0f, so just return one input.
            return q1;
        }

        if (cosHalfAngle < 0.0f)
        {
            q2.xyz = -q2.xyz;
            q2.w = -q2.w;
            cosHalfAngle = -cosHalfAngle;
        }

        float blendA;
        float blendB;
        if (cosHalfAngle < 0.99f)
        {
            // do proper slerp for big angles
            float halfAngle = acos(cosHalfAngle);
            float sinHalfAngle = sin(halfAngle);
            float oneOverSinHalfAngle = 1.0f / sinHalfAngle;
            blendA = sin(halfAngle * (1.0f - t)) * oneOverSinHalfAngle;
            blendB = sin(halfAngle * t) * oneOverSinHalfAngle;
        }
        else
        {
            // do lerp if angle is really small.
            blendA = 1.0f - t;
            blendB = t;
        }

        Quaternion result = Quaternion((blendA * q1.xyz) + (blendB * q2.xyz), (blendA * q1.w) + (blendB * q2.w));
        if (result.LengthSquared() > 0.0f)
        {
            return Normalize(result);
        }

        return GetIdentity();
    }

    bool Quaternion::operator ==(const Quaternion &rhs) const
    {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }

    bool Quaternion::operator !=(const Quaternion &rhs) const
    {
        return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
    }

    Quaternion Quaternion::operator-() const 
    {
        return Quaternion(-x, -y, -z, -w);
    }
};