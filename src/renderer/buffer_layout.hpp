#pragma once

#include <glad/gl.h>
#include <string>
#include <vector>
#include <initializer_list>
#include <utility>

struct BufferElement {
    std::string name;
    GLenum type{GL_FLOAT};
    GLuint count{0};
    GLboolean normalized{GL_FALSE};
    size_t offset{0};

    BufferElement() = default;
    BufferElement(std::string name, GLenum type, GLuint count, GLboolean normalized = GL_FALSE)
        : name(std::move(name)), type(type), count(count), normalized(normalized) {}

    [[nodiscard]] static auto getTypeSize(GLenum type) -> GLuint {
        switch (type) {
        case GL_FLOAT:
            return sizeof(float);
        case GL_INT:
            return sizeof(int);
        case GL_UNSIGNED_INT:
            return sizeof(unsigned int);
        case GL_BOOL:
            return sizeof(bool);
        case GL_UNSIGNED_BYTE:
            return sizeof(unsigned char);
        default:
            return 0;
        }
    }

    [[nodiscard]] auto getSize() const -> GLuint { return getTypeSize(type) * count; }
};

class BufferLayout {
public:
    BufferLayout() = default;
    BufferLayout(std::initializer_list<BufferElement> elements) : elements_(elements) {
        calculateOffsetsAndStride();
    }

    [[nodiscard]] auto getStride() const -> GLsizei { return stride_; }
    [[nodiscard]] auto getElements() const -> const std::vector<BufferElement> & {
        return elements_;
    }

    [[nodiscard]] auto begin() { return elements_.begin(); }
    [[nodiscard]] auto end() { return elements_.end(); }
    [[nodiscard]] auto begin() const { return elements_.begin(); }
    [[nodiscard]] auto end() const { return elements_.end(); }

private:
    std::vector<BufferElement> elements_;
    GLsizei stride_{0};

    void calculateOffsetsAndStride() {
        size_t offset = 0;
        stride_ = 0;
        for (auto &element : elements_) {
            element.offset = offset;
            offset += element.getSize();
            stride_ += static_cast<GLsizei>(element.getSize());
        }
    }
};