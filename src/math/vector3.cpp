#include "vector3.hpp"

#include <cmath>
#include <format>
#include <ostream>

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

Vector3 Vector3::operator-() const noexcept
{
    return {-x, -y, -z};
}

Vector3 Vector3::operator*(
    float scalar
) const noexcept
{
    return {x * scalar, y * scalar, z * scalar};
}

Vector3 Vector3::operator*(
    const Vector3& other
) const noexcept
{
    return {x * other.x, y * other.y, z * other.z};
}

Vector3 Vector3::operator/(
    float scalar
) const noexcept
{
    return {x / scalar, y / scalar, z / scalar};
}

Vector3& Vector3::operator+=(
    const Vector3& other
) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(
    const Vector3& other
) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(float scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& other) noexcept
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3& Vector3::operator/=(float scalar) noexcept
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

bool Vector3::operator==(
    const Vector3& other
) const noexcept
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(
    const Vector3& other
) const noexcept
{
    return !(*this == other);
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

float Vector3::distance(
    const Vector3& other
) const noexcept
{
    return (*this - other).length();
}

Vector3 Vector3::lerp(
    const Vector3& other,
    float t
) const noexcept
{
    return *this + (other - *this) * t;
}

std::ostream& operator<<(std::ostream& ostream, const Vector3& vec3){
    ostream <<std::format("vec3: x:{},y:{},z:{}", vec3.x , vec3.y,  vec3.z);
    return ostream;
}

Vector3 operator*(
    float scalar,
    const Vector3& vec3
) noexcept
{
    return vec3 * scalar;
}
