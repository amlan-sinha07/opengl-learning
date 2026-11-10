#include "index_buffer.hpp"
#include "../rendering/gl_helper.hpp"
#include <stdexcept>

namespace {
    constexpr GLenum TARGET = GL_ELEMENT_ARRAY_BUFFER;
}

IndexBuffer::IndexBuffer(
    const unsigned int* data,
    unsigned int count
)
    : m_id(0),
      m_count(count)
{
    if (data==nullptr || count==0){
        throw std::invalid_argument("IndexBuffer: invalid index data.");
    }

    m_id = GLHelper::createAndUploadBuffer(
        TARGET,
        static_cast<size_t>(count) * sizeof(unsigned int),
        data,
        GL_STATIC_DRAW
    );
}

IndexBuffer::~IndexBuffer() {
    if (m_id != 0) {
        GLHelper::destroyBuffer(m_id);
    }
}

IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept
    : m_id(other.m_id), m_count(other.m_count) {
    other.m_id = 0;
    other.m_count = 0;
}

IndexBuffer &IndexBuffer::operator=(IndexBuffer &&other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            GLHelper::destroyBuffer(m_id);
        }

        m_id = other.m_id;
        m_count = other.m_count;

        other.m_id = 0;
        other.m_count = 0;
    }
    return *this;
}

void IndexBuffer::bind() const
{
    GLHelper::bindBuffer(TARGET, m_id);
}

void IndexBuffer::unbind() const
{
    GLHelper::bindBuffer(TARGET, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return m_count;
}
GLuint IndexBuffer::getId() const
{
    return m_id;
}