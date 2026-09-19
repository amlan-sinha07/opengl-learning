#include "index_buffer.hpp"
#include "gl_helper.hpp"

IndexBuffer::IndexBuffer(
    const unsigned int* data,
    unsigned int count
)
    : m_id(0),
      m_count(count)
{
    m_id = GLHelper::createAndUploadBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        count * sizeof(unsigned int),
        data,
        GL_STATIC_DRAW
    );
}

IndexBuffer::~IndexBuffer()
{
    GLHelper::destroyBuffer(m_id);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return m_count;
}