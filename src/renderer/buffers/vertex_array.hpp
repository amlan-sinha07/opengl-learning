#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "buffer_layout.hpp"

class VertexArray
{
private:
    GLuint m_id{0};
    /* automatically calculated */
    GLuint m_attributeIndex{0};
    GLuint m_bindingIndex{0};

public:
    VertexArray();
    ~VertexArray();

    // No copying
    VertexArray(const VertexArray&) = delete;
    auto operator=(const VertexArray&) -> VertexArray& = delete;

    VertexArray(VertexArray&& other) noexcept;
    auto operator=(VertexArray&& other) noexcept -> VertexArray&;

    void bind() const;
    void unbind() const;

    void addVertexBuffer(
        const VertexBuffer& vbo,
        const BufferLayout& layout
    );

    [[nodiscard]]
    auto getId() const -> GLuint
    {
        return m_id;
    }
};