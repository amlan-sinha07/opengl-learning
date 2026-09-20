#pragma once
#pragma once

#include "mesh.hpp"
#include "shader.hpp"

class Renderer {
public:
    void clear() const;

    void draw(
        const Mesh& mesh,
        Shader& shader
    ) const;
};