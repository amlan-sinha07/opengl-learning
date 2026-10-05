#pragma once

#include "../../math/vector3.hpp"

struct Vertex {
    Vector3 position;
    Vector3 color;

    Vertex() = default;

    Vertex(
        const Vector3& pos,
        const Vector3& col
    )
        : position{pos},
          color{col}
    {
    }
};
