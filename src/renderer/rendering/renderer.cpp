#include "renderer.hpp"

void Renderer::clear_color(const std::array<float, 4> &bgColor) const {
    GLHelper::clearColor(bgColor);
}

void Renderer::draw(const Mesh &mesh, Shader &shader) const {
    shader.use();

    mesh.bind();

    GLHelper::drawElements(mesh.getVAO(), mesh.getEBO(), mesh.getPrimitiveMode(),
                           mesh.getIndexCount());

    mesh.unbind();
}