#include "vector4.hpp"

#include <cmath>
#include <format>
#include <ostream>

Vector4 Vector4::operator+(
    const Vector4& other
) const noexcept
{
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Vector4 Vector4::operator-(
    const Vector4& other
) const noexcept
{
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Vector4 Vector4::operator-() const noexcept
{
    return {-x, -y, -z, -w};
}

Vector4 Vector4::operator*(
    float scalar
) const noexcept
{
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

Vector4 Vector4::operator*(
    const Vector4& other
) const noexcept
{
    return {x * other.x, y * other.y, z * other.z, w * other.w};
}

Vector4 Vector4::operator/(
    float scalar
) const noexcept
{
    return {x / scalar, y / scalar, z / scalar, w / scalar};
}

Vector4& Vector4::operator+=(
    const Vector4& other
) noexcept
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vector4& Vector4::operator-=(
    const Vector4& other
) noexcept
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vector4& Vector4::operator*=(float scalar) noexcept
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vector4& Vector4::operator*=(const Vector4& other) noexcept
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;
    return *this;
}

Vector4& Vector4::operator/=(float scalar) noexcept
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

bool Vector4::operator==(
    const Vector4& other
) const noexcept
{
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vector4::operator!=(
    const Vector4& other
) const noexcept
{
    return !(*this == other);
}

float Vector4::dot(
    const Vector4& other
) const noexcept
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

float Vector4::lengthSquared() const noexcept
{
    return dot(*this);
}

float Vector4::length() const noexcept
{
    return std::sqrt(lengthSquared());
}

Vector4 Vector4::normalized() const noexcept
{
    const float currentLength = length();
    if (currentLength == 0.0f) {
        return *this;
    }

    return *this / currentLength;
}

float Vector4::distance(
    const Vector4& other
) const noexcept
{
    return (*this - other).length();
}

Vector4 Vector4::lerp(
    const Vector4& other,
    float t
) const noexcept
{
    return *this + (other - *this) * t;
}

std::ostream& operator<<(std::ostream& ostream, const Vector4& vec4){
    ostream <<std::format("vec4: x:{},y:{},z:{},w:{}", vec4.x, vec4.y, vec4.z, vec4.w);
    return ostream;
}

Vector4 operator*(
    float scalar,
    const Vector4& vec4
) noexcept
{
    return vec4 * scalar;
}
