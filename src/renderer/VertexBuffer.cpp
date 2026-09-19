#include "VertexBuffer.hpp"
#include "gl_helper.hpp"

VertexBuffer::VertexBuffer(
    const void* data,
    GLsizeiptr size,
    GLenum usage
)
    : rendererID(
        GLHelper::createAndUploadBuffer(GL_ARRAY_BUFFER, size, data, usage)
    ){
    //GLHelper::bindVertexBuffer(rendererID);
    //GLHelper::setVertexBufferData(rendererID,data,size,usage);
    }

VertexBuffer::~VertexBuffer()
{
    GLHelper::destroyBuffer(rendererID);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : rendererID(other.rendererID),
      size(other.size)
{
    other.rendererID = 0;
    other.size = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {
        GLHelper::destroyBuffer(rendererID);

        rendererID = other.rendererID;
        size = other.size;

        other.rendererID = 0;
        other.size = 0;
    }

    return *this;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VertexBuffer::getID() const
{
    return rendererID;
}

GLsizeiptr VertexBuffer::getSize() const
{
    return size;
}