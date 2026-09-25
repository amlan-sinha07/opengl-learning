#include "math/vector3.hpp"

#include <cassert>
#include <cmath>

namespace {
    constexpr bool nearlyEqual(float first, float second) {
        return std::abs(first - second) < 0.0001f;
    }

    constexpr bool nearlyEqual(
        const Vector3& first,
        const Vector3& second
    ) {
        return nearlyEqual(first.x, second.x)
            && nearlyEqual(first.y, second.y)
            && nearlyEqual(first.z, second.z);
    }
}

int main() {
    const Vector3 xAxis{1.0f, 0.0f, 0.0f};
    const Vector3 yAxis{0.0f, 1.0f, 0.0f};

    assert(nearlyEqual(
        xAxis.cross(yAxis),
        Vector3{0.0f, 0.0f, 1.0f}
    ));
    assert(nearlyEqual(xAxis.dot(yAxis), 0.0f));
    assert(nearlyEqual(xAxis.length(), 1.0f));
    assert(nearlyEqual(
        Vector3{3.0f, 4.0f, 0.0f}.length(),
        5.0f
    ));
    assert(nearlyEqual(
        Vector3{3.0f, 4.0f, 0.0f}.normalized(),
        Vector3{0.6f, 0.8f, 0.0f}
    ));
    assert(nearlyEqual(
        Vector3{1.0f, 2.0f, 3.0f} + Vector3{4.0f, 5.0f, 6.0f},
        Vector3{5.0f, 7.0f, 9.0f}
    ));
    assert(nearlyEqual(
        Vector3{2.0f, 4.0f, 6.0f} / 2.0f,
        Vector3{1.0f, 2.0f, 3.0f}
    ));

    return 0;
}
