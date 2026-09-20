#include "renderer.hpp"
#include "gl_helper.hpp"

void Renderer::clear() const
{
    const std::array<float, 4> color{
        0.1f, 0.1f, 0.1f, 1.0f
    };

    GLHelper::clearFrame(color);
}

void Renderer::draw(
    const Mesh& mesh,
    Shader& shader
) const
{
    shader.use();

    mesh.bind();

    GLHelper::drawElements(
        mesh.getVAO(),
        mesh.getEBO(),
        mesh.getPrimitiveMode(),
        mesh.getIndexCount()
    );

    mesh.unbind();
}