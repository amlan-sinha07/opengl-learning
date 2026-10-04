#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "buffer_layout.hpp"

class VertexArray
{
private:
    GLuint m_id{0};
    GLuint m_attributeIndex{0};
    GLuint m_bindingIndex{0};

public:
    VertexArray();
    ~VertexArray();

    // No copying
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    // Only moving. Generated move ops copy the counters and leave the source's
    // members untouched, so the source VAO keeps a live GL name and would be
    // deleted twice by ~VertexArray. Moving a VertexArray is therefore not
    // safe -- only construct it in place.
    VertexArray(VertexArray&&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;

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