#include "gl_helper.hpp"
#include "../core/logger.hpp"

namespace GLHelper {

    auto createAndUploadBuffer(GLenum target, size_t sizeBytes, const void* data, GLenum usage) -> GLuint {
        GLuint id{0};
        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, static_cast<GLsizeiptr>(sizeBytes), data, usage);
        glBindBuffer(target, 0);
        return id;
    }

    void bindVertexBuffer(GLuint id){
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void setVertexBufferData(GLuint id, const void* data, size_t size, GLenum usage){
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(size), data, usage);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void updateBufferSubData(GLenum target, GLuint bufferId, size_t offsetBytes, size_t sizeBytes, const void* data) {
        glBindBuffer(target, bufferId);
        glBufferSubData(target, static_cast<GLintptr>(offsetBytes), static_cast<GLsizeiptr>(sizeBytes), data);
        glBindBuffer(target, 0);
    }

    void destroyBuffer(GLuint bufferId) {
        if (bufferId != 0) {
            glDeleteBuffers(1, &bufferId);
        }
    }

    auto createVertexArray() -> GLuint {
        GLuint id{0};
        glGenVertexArrays(1, &id);
        return id;
    }

    void destroyVertexArray(GLuint vaoId) {
        if (vaoId != 0) {
            glDeleteVertexArrays(1, &vaoId);
        }
    }

    void attachLayoutToVAO(GLuint vaoId, GLuint vboId, const BufferLayout& layout, GLuint bindingSlot, GLuint& startingAttribIndex) {
        glBindVertexArray(vaoId);
        glBindVertexBuffer(bindingSlot, vboId, 0, layout.getStride());

        for (const auto& element : layout.getElements()) {
            glVertexAttribFormat(
                startingAttribIndex,
                static_cast<GLint>(element.count),
                element.type,
                element.normalized,
                static_cast<GLuint>(element.offset)
            );
            glVertexAttribBinding(startingAttribIndex, bindingSlot);
            glEnableVertexAttribArray(startingAttribIndex);
            startingAttribIndex++;
        }

        glBindVertexArray(0);
    }

    static auto compileSingleShader(GLenum type, std::string_view source) -> GLuint {
        GLuint shader = glCreateShader(type);
        const char* src = source.data();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            KERROR("Shader compilation error (%s):\n%s",
                   type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
        }
        return shader;
    }

    auto createShaderProgram(std::string_view vertexSrc, std::string_view fragmentSrc) -> GLuint {
        GLuint vert = compileSingleShader(GL_VERTEX_SHADER, vertexSrc);
        GLuint frag = compileSingleShader(GL_FRAGMENT_SHADER, fragmentSrc);

        GLuint program = glCreateProgram();
        glAttachShader(program, vert);
        glAttachShader(program, frag);
        glLinkProgram(program);

        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            KERROR("Shader program link error:\n%s", infoLog);
        }

        glDeleteShader(vert);
        glDeleteShader(frag);

        return program;
    }

    void destroyShaderProgram(GLuint programId) {
        if (programId != 0) {
            glDeleteProgram(programId);
        }
    }

    void clearFrame(const std::array<float, 4>& color, GLbitfield mask) {
        glClearColor(color[0], color[1], color[2], color[3]);
        glClear(mask);
    }

    void drawArrays(GLuint vaoId, GLenum primitiveMode, GLsizei count, GLint first) {
        glBindVertexArray(vaoId);
        glDrawArrays(primitiveMode, first, count);
        glBindVertexArray(0);
    }

    void drawElements(GLuint vaoId, GLuint eboId, GLenum primitiveMode, GLsizei count) {
        glBindVertexArray(vaoId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
        glDrawElements(primitiveMode, count, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

}