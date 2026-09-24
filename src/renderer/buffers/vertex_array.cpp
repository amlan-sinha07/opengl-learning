#include "vertex_array.hpp"
#include "../rendering/gl_helper.hpp"
#include <utility>

VertexArray::VertexArray() : m_id(GLHelper::createVertexArray()) {}

VertexArray::~VertexArray() {
    GLHelper::destroyVertexArray(m_id);
}

VertexArray::VertexArray(VertexArray &&other) noexcept
    : m_id(std::exchange(other.m_id, 0)),
      m_attributeIndex(std::exchange(other.m_attributeIndex, 0)),
      m_bindingIndex(std::exchange(other.m_bindingIndex, 0)) {}

auto VertexArray::operator=(VertexArray &&other) noexcept -> VertexArray & {
    if (this != &other) {
        GLHelper::destroyVertexArray(m_id);
        m_id = std::exchange(other.m_id, 0);
        m_attributeIndex = std::exchange(other.m_attributeIndex, 0);
        m_bindingIndex = std::exchange(other.m_bindingIndex, 0);
    }
    return *this;
}

void VertexArray::bind() const { glBindVertexArray(m_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(const VertexBuffer &vbo, const BufferLayout &layout) {
    GLHelper::attachLayoutToVAO(m_id, vbo.getId(), layout, m_bindingIndex, m_attributeIndex);
    m_bindingIndex++;
}