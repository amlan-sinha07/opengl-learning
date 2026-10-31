#pragma once

#include "../mesh/mesh.hpp"
#include "../shader/shader.hpp"
#include "gl_helper.hpp"


class Renderer {
public:
    Renderer()=default;

    template<typename... ClearBits>
    void clear_bits(ClearBits... masks) const {
        static_assert((std::is_same_v<ClearBits, int> || ...), "All fields must be of type GLbitfield");
        GLbitfield mask = (static_cast<GLbitfield>(masks) | ...);
        GLHelper::clearMask(mask);
    }

    void clear_color(const std::array<float, 4> &bgColor={0.0F,0.0F,0.0F,0.0F}) const;

    void draw(const Mesh &mesh, Shader &shader) const;

};