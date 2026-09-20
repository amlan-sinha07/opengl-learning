#include "index_buffer.hpp"
#include "gl_helper.hpp"
#include <stdexcept>

IndexBuffer::IndexBuffer(
    const unsigned int* data,
    unsigned int count
)
    : m_count(count)
{
    if (data==nullptr || count==0){
        throw std::invalid_argument("IndexBuffer: invalid index data.");
    }
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_id);

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(count * sizeof(unsigned int)),
        data,
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
IndexBuffer::~IndexBuffer()
{
    if (m_id !=0){
        glDeleteBuffers(1, &m_id);
    }
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
GLuint IndexBuffer::getId() const
{
    return m_id;
}