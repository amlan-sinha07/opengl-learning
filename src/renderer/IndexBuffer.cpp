#include "IndexBuffer.hpp"
#include "gl_helper.hpp"

IndexBuffer::IndexBuffer(
    const unsigned int* data,
    unsigned int count
)
    : m_RenderedID(0),
      m_Count(count)
{
    m_RenderedID = GLHelper::createAndUploadBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        count * sizeof(unsigned int),
        data,
        GL_STATIC_DRAW
    );
}

IndexBuffer::~IndexBuffer()
{
    GLHelper::destroyBuffer(m_RenderedID);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return m_Count;
}