#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include <vector>

#include "vertex.hpp"
#include "../buffers/vertex_buffer.hpp"
#include "../buffers/vertex_array.hpp"
#include "../buffers/index_buffer.hpp"
#include "../buffers/buffer_layout.hpp"

class Mesh {
private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    IndexBuffer m_ebo;
    GLenum m_primitiveMode;

public:
    Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices,
         GLenum primitiveMode = GL_TRIANGLES);

    ~Mesh() = default;

    // No copying
    Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;

    // Moving allowed
    Mesh(Mesh &&) noexcept;
    auto operator=(Mesh &&) noexcept -> Mesh &;

    void bind() const;
    void unbind() const;
    void updateVertices(const std::vector<MeshVertex> &vertices);

    [[nodiscard]] auto getVAO() const -> GLuint;
    [[nodiscard]] auto getEBO() const -> GLuint;
    [[nodiscard]] auto getIndexCount() const -> GLsizei;
    [[nodiscard]] auto getPrimitiveMode() const -> GLenum;
};