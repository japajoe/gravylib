#include "Quaternion.hpp"
#include <cmath>

namespace Gravy::System::Numerics
{
    Quaternion::Quaternion()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 1;
    }

    Quaternion::Quaternion(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    Quaternion::Quaternion(const Quaternion &q)
    {
        this->x = q.x;
        this->y = q.y;
        this->z = q.z;
        this->w = q.w;
    }

    float Quaternion::Length() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    float Quaternion::LengthSquared() const
    {
        return x * x + y * y + z * z + w * w;
    }

    void Quaternion::Normalize()
    {
        float len = Length();
        if (len != 0)
        {
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }

    Vector3 Quaternion::ToEulerAngles() const
    {
        // Vector3 euler;

        // // roll (x-axis rotation)
        // float sinr_cosp = 2 * (w * x + y * z);
        // float cosr_cosp = 1 - 2 * (x * x + y * y);
        // euler.x = std::atan2(sinr_cosp, cosr_cosp);

        // // pitch (y-axis rotation)
        // float sinp = 2 * (w * y - z * x);
        // if (std::abs(sinp) >= 1)
        //     euler.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        // else
        //     euler.y = std::asin(sinp);

        // // yaw (z-axis rotation)
        // float siny_cosp = 2 * (w * z + x * y);
        // float cosy_cosp = 1 - 2 * (y * y + z * z);
        // euler.z = std::atan2(siny_cosp, cosy_cosp);

        // return euler;

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

    // Static method to convert a quaternion to Euler angles
    Vector3 Quaternion::ToEulerAngles(const Quaternion &q)
    {
        return q.ToEulerAngles();
    }

    // Static method to normalize a quaternion
    Quaternion Quaternion::Normalize(const Quaternion &q)
    {
        Quaternion result(q);
        result.Normalize();
        return result;
    }

    // Create a quaternion from an axis-angle representation
    Quaternion Quaternion::FromAxisAngle(const Vector3 &axis, float angle)
    {
        float halfAngle = angle * 0.5f;
        float s = std::sin(halfAngle);
        return Quaternion(axis.x * s, axis.y * s, axis.z * s, std::cos(halfAngle));
    }

    // Create a quaternion from Euler angles
    Quaternion Quaternion::Euler(float x, float y, float z)
    {
        float cy = std::cos(z * 0.5f);
        float sy = std::sin(z * 0.5f);
        float cp = std::cos(y * 0.5f);
        float sp = std::sin(y * 0.5f);
        float cr = std::cos(x * 0.5f);
        float sr = std::sin(x * 0.5f);

        float w = cr * cp * cy + sr * sp * sy;
        x = sr * cp * cy - cr * sp * sy;
        y = cr * sp * cy + sr * cp * sy;
        z = cr * cp * sy - sr * sp * cy;

        return Quaternion(x, y, z, w);
    }

    Quaternion Quaternion::operator+(const Quaternion& q) const 
    {
        return Quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
    }

    Quaternion Quaternion::operator-(const Quaternion& q) const 
    {
        return Quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
    }

    Quaternion Quaternion::operator*(const Quaternion& q) const 
    {
        float newX = w * q.x + x * q.w + y * q.z - z * q.y;
        float newY = w * q.y - x * q.z + y * q.w + z * q.x;
        float newZ = w * q.z + x * q.y - y * q.x + z * q.w;
        float newW = w * q.w - x * q.x - y * q.y - z * q.z;
        return Quaternion(newX, newY, newZ, newW);
    }

    Quaternion Quaternion::operator*(float scalar) const 
    {
        return Quaternion(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Quaternion Quaternion::operator/(float scalar) const 
    {
        if (scalar != 0) 
        {
            float invScalar = 1.0f / scalar;
            return Quaternion(x * invScalar, y * invScalar, z * invScalar, w * invScalar);
        }
        return Quaternion();
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