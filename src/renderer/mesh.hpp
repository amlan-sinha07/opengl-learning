#pragma once

#include <glad/gl.h>

#include <vector>

#include "vertex.hpp"
#include "vertex_buffer.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "buffer_layout.hpp"

class Mesh {
private:
    VertexArray m_vao;
    VertexBuffer m_vbo;
    IndexBuffer m_ebo;
    GLenum m_primitiveMode;

public:
    Mesh(
        const std::vector<Vertex>& vertices,
        const std::vector<unsigned int>& indices,
        GLenum primitiveMode = GL_TRIANGLES
    );

    ~Mesh() = default;

    // No copying
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // Moving allowed
    Mesh(Mesh&&) noexcept = default;
    Mesh& operator=(Mesh&&) noexcept = default;

    void bind() const;
    void unbind() const;

    GLuint getVAO() const;
    GLuint getEBO() const;
    GLsizei getIndexCount() const;
    GLenum getPrimitiveMode() const;
};