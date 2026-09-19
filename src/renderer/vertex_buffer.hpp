#pragma once

#include <glad/gl.h>
#include <cstddef>

class VertexBuffer
{
private:
    GLuint m_id;
    GLsizeiptr m_size;

public:
    VertexBuffer(const void* data, GLsizeiptr size,
                 GLenum usage = GL_STATIC_DRAW);

    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void bind() const;
    void unbind() const;

    GLuint getId() const;
    GLsizeiptr getSize() const;
};