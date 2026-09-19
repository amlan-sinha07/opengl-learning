#pragma once

#include "../../dependencies/include/glad/gl.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include <cstddef>
#include <array>
#include <string_view>
#include "buffer_layout.hpp"


namespace GLHelper
{
    [[nodiscard]] auto createAndUploadBuffer(GLenum target, size_t sizeBytes, const void* data, GLenum usage) -> GLuint;
    void bindVertexBuffer(GLuint id);
    void setVertexBufferData(GLuint id, const void* data, size_t size, GLenum usage);
    void updateBufferSubData(GLenum target, GLuint bufferId, size_t offsetBytes, size_t sizeBytes, const void* data);
    void destroyBuffer(GLuint bufferId);

    [[nodiscard]] auto createVertexArray() -> GLuint;
    void destroyVertexArray(GLuint vaoId);
    void attachLayoutToVAO(GLuint vaoId, GLuint vboId, const BufferLayout& layout, GLuint bindingSlot, GLuint& startingAttribIndex);

    [[nodiscard]] auto createShaderProgram(std::string_view vertexSrc, std::string_view fragmentSrc) -> GLuint;
    void destroyShaderProgram(GLuint programId);

    void clearFrame(const std::array<float, 4>& color, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    void drawArrays(GLuint vaoId, GLenum primitiveMode, GLsizei count, GLint first = 0);
    void drawElements(GLuint vaoId, GLuint eboId, GLenum primitiveMode, GLsizei count);
}

