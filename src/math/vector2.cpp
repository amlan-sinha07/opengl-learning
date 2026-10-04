#include "vector2.hpp"

#include <cmath>
#include <format>
#include <ostream>

Vector2 Vector2::operator+(
    const Vector2& other
) const noexcept
{
    return {x + other.x, y + other.y};
}

Vector2 Vector2::operator-(
    const Vector2& other
) const noexcept
{
    return {x - other.x, y - other.y};
}

Vector2 Vector2::operator-() const noexcept
{
    return {-x, -y};
}

Vector2 Vector2::operator*(
    float scalar
) const noexcept
{
    return {x * scalar, y * scalar};
}

Vector2 Vector2::operator*(
    const Vector2& other
) const noexcept
{
    return {x * other.x, y * other.y};
}

Vector2 Vector2::operator/(
    float scalar
) const noexcept
{
    return {x / scalar, y / scalar};
}

Vector2& Vector2::operator+=(
    const Vector2& other
) noexcept
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(
    const Vector2& other
) noexcept
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2& Vector2::operator*=(
    float scalar
) noexcept
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator*=(
    const Vector2& other
) noexcept
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2& Vector2::operator/=(
    float scalar
) noexcept
{
    x /= scalar;
    y /= scalar;
    return *this;
}

bool Vector2::operator==(
    const Vector2& other
) const noexcept
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(
    const Vector2& other
) const noexcept
{
    return !(*this == other);
}

float Vector2::dot(
    const Vector2& other
) const noexcept
{
    return x * other.x + y * other.y;
}

float Vector2::lengthSquared() const noexcept
{
    return dot(*this);
}

float Vector2::length() const noexcept
{
    return std::sqrt(lengthSquared());
}

Vector2 Vector2::normalized() const noexcept
{
    const float currentLength = length();
    if (currentLength == 0.0f) {
        return *this;
    }

    return *this / currentLength;
}

float Vector2::distance(
    const Vector2& other
) const noexcept
{
    return (*this - other).length();
}

Vector2 Vector2::lerp(
    const Vector2& other,
    float t
) const noexcept
{
    return *this + (other - *this) * t;
}

std::ostream& operator<<(std::ostream& ostream, const Vector2& vec2){
    ostream <<std::format("vec2: x:{},y:{}", vec2.x, vec2.y);
    return ostream;
}

Vector2 operator*(
    float scalar,
    const Vector2& vec2
) noexcept
{
    return vec2 * scalar;
}
