#pragma once

#include <iosfwd>

class Vector4 {
public:
    constexpr Vector4() = default;
    constexpr Vector4(float x, float y, float z, float w)
        : x{x}, y{y}, z{z}, w{w} {}

    [[nodiscard]] Vector4 operator+(const Vector4& other) const noexcept;
    [[nodiscard]] Vector4 operator-(const Vector4& other) const noexcept;
    [[nodiscard]] Vector4 operator-() const noexcept;
    [[nodiscard]] Vector4 operator*(float scalar) const noexcept;
    [[nodiscard]] Vector4 operator*(const Vector4& other) const noexcept;
    [[nodiscard]] Vector4 operator/(float scalar) const noexcept;

    Vector4& operator+=(const Vector4& other) noexcept;
    Vector4& operator-=(const Vector4& other) noexcept;
    Vector4& operator*=(float scalar) noexcept;
    Vector4& operator*=(const Vector4& other) noexcept;
    Vector4& operator/=(float scalar) noexcept;

    [[nodiscard]] bool operator==(const Vector4& other) const noexcept;
    [[nodiscard]] bool operator!=(const Vector4& other) const noexcept;

    [[nodiscard]] float dot(const Vector4& other) const noexcept;
    [[nodiscard]] float lengthSquared() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] Vector4 normalized() const noexcept;
    [[nodiscard]] float distance(const Vector4& other) const noexcept;
    [[nodiscard]] Vector4 lerp(const Vector4& other, float t) const noexcept;

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    float w{0.0f};
};

std::ostream& operator<<(std::ostream& ostream, const Vector4& vec4);
[[nodiscard]] Vector4 operator*(float scalar, const Vector4& vec4) noexcept;
