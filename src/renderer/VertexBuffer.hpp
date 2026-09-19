#pragma once

#include "../../dependencies/include/glad/gl.h"
#include <cstddef>

class VertexBuffer
{
private:
    GLuint rendererID;
    GLsizeiptr size;

public:
    VertexBuffer(const void* data, GLsizeiptr size,
                 GLenum usage = GL_STATIC_DRAW);

    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    VertexBuffer(VertexBuffer&& other) noexcept;
    VertexBuffer& operator=(VertexBuffer&& other) noexcept;

    void Bind() const;
    void Unbind() const;

    GLuint getID() const;
    GLsizeiptr getSize() const;
};