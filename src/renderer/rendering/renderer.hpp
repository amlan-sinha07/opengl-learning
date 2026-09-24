#pragma once
#pragma once

#include "../mesh/mesh.hpp"
#include "../shader/shader.hpp"

class Renderer {
public:
    void clear() const;

    void draw(
        const Mesh& mesh,
        Shader& shader
    ) const;
};