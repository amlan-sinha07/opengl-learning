#include "vao.hpp"
#include "gl_helper.hpp"
#include <utility>

VertexArray::VertexArray() : m_RendererID_(GLHelper::createVertexArray()) {}

VertexArray::~VertexArray() {
    GLHelper::destroyVertexArray(m_RendererID_);
}

VertexArray::VertexArray(VertexArray &&other) noexcept
    : m_RendererID_(std::exchange(other.m_RendererID_, 0)),
      m_attribute_index_(std::exchange(other.m_attribute_index_, 0)),
      m_binding_index_(std::exchange(other.m_binding_index_, 0)) {}

auto VertexArray::operator=(VertexArray &&other) noexcept -> VertexArray & {
    if (this != &other) {
        GLHelper::destroyVertexArray(m_RendererID_);
        m_RendererID_ = std::exchange(other.m_RendererID_, 0);
        m_attribute_index_ = std::exchange(other.m_attribute_index_, 0);
        m_binding_index_ = std::exchange(other.m_binding_index_, 0);
    }
    return *this;
}

void VertexArray::bind() const { glBindVertexArray(m_RendererID_); }

void VertexArray::unbind() const { glBindVertexArray(0); }

void VertexArray::addVertexBuffer(const VertexBuffer &vbo, const BufferLayout &layout) {
    GLHelper::attachLayoutToVAO(m_RendererID_, vbo.getID(), layout, m_binding_index_, m_attribute_index_);
    m_binding_index_++;
}