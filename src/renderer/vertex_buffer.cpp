#include "vertex_buffer.hpp"
#include "gl_helper.hpp"

VertexBuffer::VertexBuffer(
    const void* data,
    GLsizeiptr size,
    GLenum usage
)
    : m_id(
        GLHelper::createAndUploadBuffer(GL_ARRAY_BUFFER, size, data, usage)
    ){
    }

VertexBuffer::~VertexBuffer()
{
    GLHelper::destroyBuffer(m_id);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
    : m_id(other.m_id),
      m_size(other.m_size)
{
    other.m_id = 0;
    other.m_size = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
{
    if (this != &other)
    {
        GLHelper::destroyBuffer(m_id);

        m_id = other.m_id;
        m_size = other.m_size;

        other.m_id = 0;
        other.m_size = 0;
    }

    return *this;
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint VertexBuffer::getId() const
{
    return m_id;
}

GLsizeiptr VertexBuffer::getSize() const
{
    return m_size;
}