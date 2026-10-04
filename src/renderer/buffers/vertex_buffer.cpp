#include "vertex_buffer.hpp"
#include "../rendering/gl_helper.hpp"

namespace {
    constexpr GLenum TARGET = GL_ARRAY_BUFFER;
}

VertexBuffer::VertexBuffer(
    const void* data,
    GLsizeiptr size,
    GLenum usage
)
    : m_id(
        GLHelper::createAndUploadBuffer(TARGET, size, data, usage)
    ),
      m_size(size)
    {
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
    GLHelper::bindBuffer(TARGET, m_id);
}

void VertexBuffer::unbind() const
{
    GLHelper::bindBuffer(TARGET, 0);
}

void VertexBuffer::update(
    const void* data,
    GLsizeiptr size
)
{
    GLHelper::updateBufferSubData(TARGET, m_id, 0, size, data);
}

GLuint VertexBuffer::getId() const
{
    return m_id;
}

GLsizeiptr VertexBuffer::getSize() const
{
    return m_size;
}