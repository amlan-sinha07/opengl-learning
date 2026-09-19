#pragma once

#include <glad/gl.h>

#include "VertexBuffer.hpp"
#include "buffer_layout.hpp"

class VertexArray
{
private:
    GLuint m_RendererID_{0};
    GLuint m_attribute_index_{0};
    GLuint m_binding_index_{0};

public:
    VertexArray();
    ~VertexArray();

    // No copying
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    // Only moving
    VertexArray(VertexArray&& other) noexcept;
    VertexArray& operator=(VertexArray&& other) noexcept;

    void bind() const;
    void unbind() const;

    void addVertexBuffer(
        const VertexBuffer& vbo,
        const BufferLayout& layout
    );

    [[nodiscard]]
    auto getID() const -> GLuint
    {
        return m_RendererID_;
    }
};