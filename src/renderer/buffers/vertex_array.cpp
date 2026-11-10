#include "vertex_array.hpp"
#include "../rendering/gl_helper.hpp"

VertexArray::VertexArray() : m_id(GLHelper::createVertexArray()) {}

VertexArray::~VertexArray() {
    if (m_id != 0) {
        GLHelper::destroyVertexArray(m_id);
    }
}

VertexArray::VertexArray(VertexArray &&other) noexcept
    : m_id(other.m_id), m_attributeIndex(other.m_attributeIndex), m_bindingIndex(other.m_bindingIndex) {
    other.m_id = 0;
    other.m_attributeIndex = 0;
    other.m_bindingIndex = 0;
}

VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
    if (this != &other) {
        if (m_id != 0) {
            GLHelper::destroyVertexArray(m_id);
        }

        m_id = other.m_id;
        m_attributeIndex = other.m_attributeIndex;
        m_bindingIndex = other.m_bindingIndex;

        other.m_id = 0;
        other.m_attributeIndex = 0;
        other.m_bindingIndex = 0;
    }
    return *this;
}

void VertexArray::bind() const { glBindVertexArray(m_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(const VertexBuffer &vbo, const BufferLayout &layout) {
    GLHelper::attachLayoutToVAO(m_id, vbo.getId(), layout, m_bindingIndex, m_attributeIndex);
    m_bindingIndex++;
}