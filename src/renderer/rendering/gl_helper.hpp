#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <array>
#include <string_view>
#include <type_traits>
#include "../buffers/buffer_layout.hpp"

namespace GLHelper {
    constexpr int LOG_BUFFER = 512;

// Buffer management. All raw buffer calls in the project route through these.
[[nodiscard]] auto createAndUploadBuffer([[maybe_unused]] GLenum target, size_t sizeBytes,
                                         const void *data, GLenum usage) -> GLuint;
void bindBuffer(GLenum target, GLuint id);
void updateBufferSubData(GLenum target, GLuint bufferId, size_t offsetBytes, size_t sizeBytes,
                         const void *data);
void destroyBuffer(GLuint bufferId);

[[nodiscard]] auto createVertexArray() -> GLuint;
void destroyVertexArray(GLuint vaoId);
// bindingSlot is used by the DSA vertex attribute binding path.
void attachLayoutToVAO(GLuint vaoId, GLuint vboId, const BufferLayout &layout, GLuint bindingSlot,
                       GLuint &startingAttribIndex);

[[nodiscard]] auto createShaderProgram(std::string_view vertexSrc, std::string_view fragmentSrc)
    -> GLuint;
void destroyShaderProgram(GLuint programId);

void clearColor(const std::array<float, 4> &color);

void clearMask(GLbitfield mask);

void drawElements(GLuint vaoId, GLuint eboId, GLenum primitiveMode, GLsizei count);

}
