#pragma once

#include <iosfwd>

class Vector3 {
public:
    constexpr Vector3() = default;
    constexpr Vector3(float x, float y, float z)
        : x{x}, y{y}, z{z} {}

    [[nodiscard]] Vector3 operator+(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 operator-(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 operator-() const noexcept;
    [[nodiscard]] Vector3 operator*(float scalar) const noexcept;
    [[nodiscard]] Vector3 operator*(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 operator/(float scalar) const noexcept;

    Vector3& operator+=(const Vector3& other) noexcept;
    Vector3& operator-=(const Vector3& other) noexcept;
    Vector3& operator*=(float scalar) noexcept;
    Vector3& operator*=(const Vector3& other) noexcept;
    Vector3& operator/=(float scalar) noexcept;

    [[nodiscard]] bool operator==(const Vector3& other) const noexcept;
    [[nodiscard]] bool operator!=(const Vector3& other) const noexcept;

    [[nodiscard]] float dot(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 cross(const Vector3& other) const noexcept;
    [[nodiscard]] float lengthSquared() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] Vector3 normalized() const noexcept;
    [[nodiscard]] float distance(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 lerp(const Vector3& other, float t) const noexcept;

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

std::ostream& operator<<(std::ostream& ostream, const Vector3& vec3);
[[nodiscard]] Vector3 operator*(float scalar, const Vector3& vec3) noexcept;
