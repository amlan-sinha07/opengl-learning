#pragma once

#include <iosfwd>

class Vector2 {
public:
    constexpr Vector2() = default;
    constexpr Vector2(float x, float y)
        : x{x}, y{y} {}

    [[nodiscard]] Vector2 operator+(const Vector2& other) const noexcept;
    [[nodiscard]] Vector2 operator-(const Vector2& other) const noexcept;
    [[nodiscard]] Vector2 operator-() const noexcept;
    [[nodiscard]] Vector2 operator*(float scalar) const noexcept;
    [[nodiscard]] Vector2 operator*(const Vector2& other) const noexcept;
    [[nodiscard]] Vector2 operator/(float scalar) const noexcept;

    Vector2& operator+=(const Vector2& other) noexcept;
    Vector2& operator-=(const Vector2& other) noexcept;
    Vector2& operator*=(float scalar) noexcept;
    Vector2& operator*=(const Vector2& other) noexcept;
    Vector2& operator/=(float scalar) noexcept;

    [[nodiscard]] bool operator==(const Vector2& other) const noexcept;
    [[nodiscard]] bool operator!=(const Vector2& other) const noexcept;

    [[nodiscard]] float dot(const Vector2& other) const noexcept;
    [[nodiscard]] float lengthSquared() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] Vector2 normalized() const noexcept;
    [[nodiscard]] float distance(const Vector2& other) const noexcept;
    [[nodiscard]] Vector2 lerp(const Vector2& other, float t) const noexcept;

    float x{0.0f};
    float y{0.0f};
};

std::ostream& operator<<(std::ostream& ostream, const Vector2& vec2);
[[nodiscard]] Vector2 operator*(float scalar, const Vector2& vec2) noexcept;
