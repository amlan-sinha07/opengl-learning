#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <array>
#include <string_view>
#include "../buffers/buffer_layout.hpp"


namespace GLHelper
{
    // Buffer management. All raw buffer calls in the project route through these.
    [[nodiscard]] auto createAndUploadBuffer(GLenum target, size_t sizeBytes, const void* data, GLenum usage) -> GLuint;
    void bindBuffer(GLenum target, GLuint id);
    void updateBufferSubData(GLenum target, GLuint bufferId, size_t offsetBytes, size_t sizeBytes, const void* data);
    void destroyBuffer(GLuint bufferId);

    [[nodiscard]] auto createVertexArray() -> GLuint;
    void destroyVertexArray(GLuint vaoId);
    // bindingSlot is only used by the OpenGL 4.x glVertexAttribBinding path.
    // The legacy glVertexAttribPointer path ignores it (kept for API stability).
    void attachLayoutToVAO(GLuint vaoId, GLuint vboId, const BufferLayout& layout, [[maybe_unused]] GLuint bindingSlot, GLuint& startingAttribIndex);

    [[nodiscard]] auto createShaderProgram(std::string_view vertexSrc, std::string_view fragmentSrc) -> GLuint;
    void destroyShaderProgram(GLuint programId);

    void clearFrame(const std::array<float, 4>& color, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    void drawElements(GLuint vaoId, GLuint eboId, GLenum primitiveMode, GLsizei count);
}

