#pragma once

class Vector3 {
public:
    constexpr Vector3() = default;
    constexpr Vector3(float x, float y, float z)
        : x{x}, y{y}, z{z} {}

    [[nodiscard]] Vector3 operator+(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 operator-(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 operator*(float scalar) const noexcept;
    [[nodiscard]] Vector3 operator/(float scalar) const noexcept;

    [[nodiscard]] float dot(const Vector3& other) const noexcept;
    [[nodiscard]] Vector3 cross(const Vector3& other) const noexcept;
    [[nodiscard]] float lengthSquared() const noexcept;
    [[nodiscard]] float length() const noexcept;
    [[nodiscard]] Vector3 normalized() const noexcept;

    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};
