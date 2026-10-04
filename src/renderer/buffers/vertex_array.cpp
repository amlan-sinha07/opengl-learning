#include "vertex_array.hpp"
#include "../rendering/gl_helper.hpp"

VertexArray::VertexArray() : m_id(GLHelper::createVertexArray()) {}

VertexArray::~VertexArray() { GLHelper::destroyVertexArray(m_id); }

void VertexArray::bind() const { glBindVertexArray(m_id); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(const VertexBuffer &vbo, const BufferLayout &layout) {
    GLHelper::attachLayoutToVAO(m_id, vbo.getId(), layout, m_bindingIndex, m_attributeIndex);
    m_bindingIndex++;
}