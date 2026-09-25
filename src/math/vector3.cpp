#include "vector3.hpp"

#include <cmath>

Vector3 Vector3::operator+(
    const Vector3& other
) const noexcept
{
    return {x + other.x, y + other.y, z + other.z};
}

Vector3 Vector3::operator-(
    const Vector3& other
) const noexcept
{
    return {x - other.x, y - other.y, z - other.z};
}

Vector3 Vector3::operator*(
    float scalar
) const noexcept
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator/(
    float scalar
) const noexcept
{
    return {x / scalar, y / scalar, z / scalar};
}

float Vector3::dot(
    const Vector3& other
) const noexcept
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(
    const Vector3& other
) const noexcept
{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

float Vector3::lengthSquared() const noexcept
{
    return dot(*this);
}

float Vector3::length() const noexcept
{
    return std::sqrt(lengthSquared());
}

Vector3 Vector3::normalized() const noexcept
{
    const float currentLength = length();
    if (currentLength == 0.0f) {
        return *this;
    }

    return *this / currentLength;
}
