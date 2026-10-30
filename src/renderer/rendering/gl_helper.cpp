#include "gl_helper.hpp"
#include "../../core/logging/logger.hpp"

namespace GLHelper {

auto createAndUploadBuffer(GLenum target, size_t sizeBytes, const void *data, GLenum usage)
    -> GLuint {
    GLuint id{0};
    glCreateBuffers(1, &id);
    glNamedBufferData(id, static_cast<GLsizei>(sizeBytes), data, usage);
    // target is only needed when we go the old gl route and do global buffer binding
    /* glBindBuffer(target, id);
    glBufferData(target, static_cast<GLsizeiptr>(sizeBytes), data, usage);
    glBindBuffer(target, 0);
    */
    KDEBUG("Created buffer {} ({} bytes)", id, sizeBytes);
    return id;
}

void bindBuffer(GLenum target, GLuint id) { glBindBuffer(target, id); }

void updateBufferSubData([[maybe_unused]] GLenum target, GLuint bufferId, size_t offsetBytes, size_t sizeBytes,
                         const void *data) {
    // DSA: update without touching GL_ARRAY_BUFFER binding state.
    glNamedBufferSubData(bufferId,
                         static_cast<GLintptr>(offsetBytes),
                         static_cast<GLsizeiptr>(sizeBytes),
                         data);
    /* Legacy: bind target, glBufferSubData, unbind. */
    /*
    glBindBuffer(target, bufferId);
    glBufferSubData(target, static_cast<GLintptr>(offsetBytes), static_cast<GLsizeiptr>(sizeBytes),
                    data);
    glBindBuffer(target, 0);
    */
}

void destroyBuffer(GLuint bufferId) {
    if (bufferId != 0) {
        glDeleteBuffers(1, &bufferId);
    }
}

auto createVertexArray() -> GLuint {
    GLuint id{0};
    glCreateVertexArrays(1, &id);
    KDEBUG("Created vertex array {}", id);
    return id;
}

void destroyVertexArray(GLuint vaoId) {
    if (vaoId != 0) {
        glDeleteVertexArrays(1, &vaoId);
    }
}

void attachLayoutToVAO(GLuint vaoId, GLuint vboId, const BufferLayout &layout,
                       GLuint bindingSlot, GLuint &startingAttribIndex) {
    // DSA: these mutate the VAO directly by ID, no need to bind it to the context.
    /* glBindVertexArray(vaoId); */

    // Attach the VBO to this VAO at bindingSlot with the layout stride.(static_cast maybe removed later)
    glVertexArrayVertexBuffer(vaoId, bindingSlot, vboId, 0, static_cast<GLsizei>(layout.getStride()));

    /* Legacy (bind-to-edit): glVertexAttribPointer reads from the currently bound
       GL_ARRAY_BUFFER. With DSA we don't rely on global GL_ARRAY_BUFFER state. */
    /* bindBuffer(GL_ARRAY_BUFFER, vboId); */

    for (const BufferElement &Element : layout.getElements()) {
        KDEBUG("loop used for {}", Element.name);

        // Enable attribute on the specific VAO by ID.
        glEnableVertexArrayAttrib(vaoId, startingAttribIndex);
        /* Legacy: glVertexAttribPointer requires VAO bound + GL_ARRAY_BUFFER bound.
           Replaced by glVertexArrayAttribFormat/glVertexArrayAttribBinding below. */
        /* glVertexAttribPointer(startingAttribIndex,
                              static_cast<GLint>(Element.count),
                              Element.type,
                              Element.normalized,
                              layout.getStride(),
                              reinterpret_cast<const void *>(Element.offset)); */

        // Describe how to interpret the raw bytes (type, count, normalized, offset).
        glVertexArrayAttribFormat(vaoId,
                                  startingAttribIndex,
                                  static_cast<GLint>(Element.count),
                                  Element.type,
                                  Element.normalized,
                                  static_cast<GLuint>(Element.offset));
        // Link this attribute to the binding slot where the VBO is attached.
        glVertexArrayAttribBinding(vaoId, startingAttribIndex, bindingSlot);

        startingAttribIndex++;
    }

    /* glBindVertexArray(0); */

    // ---------------------------------------------------------------------------
    // OpenGL 4.x alternative (DSA / "modern" path). Commented out because it is
    // harder to reason about when learning: the buffer binding is recorded inside
    // the VAO by glBindVertexBuffer, so there is no GL_ARRAY_BUFFER bind above, and
    // each attribute is wired up in two separate steps (Format, then Binding) rather
    // than one. Same result, more indirection. Uncomment to compare.
    //
    // glBindVertexBuffer(bindingSlot, vboId, 0, layout.getStride());
    // for (const auto &Element : layout.getElements()) {
    //     glVertexAttribFormat(startingAttribIndex,
    //                          static_cast<GLint>(Element.count),
    //                          Element.type,
    //                          Element.normalized,
    //                          static_cast<GLuint>(Element.offset));
    //     glVertexAttribBinding(startingAttribIndex, bindingSlot);
    //     glEnableVertexAttribArray(startingAttribIndex);
    //     startingAttribIndex++;
    // }
    // ---------------------------------------------------------------------------
}

static auto compileSingleShader(GLenum type, std::string_view source) -> GLuint {
    GLuint shader = glCreateShader(type);
    const char *src = source.data();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        KERROR("Shader compilation error ({}):\n{}",
               type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", infoLog);
    } else {
        KDEBUG("Compiled {} shader", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
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
        KERROR("Shader program link error:\n{}", infoLog);
    } else {
        KINFO("Shader program linked");
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

void clearFrame(const std::array<float, 4> &color, GLbitfield mask) {
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(mask);
}

void drawElements(GLuint vaoId, GLuint eboId, GLenum primitiveMode, GLsizei count) {
    // Attach EBO to this VAO by ID (DSA). The VAO still needs to be bound to the
    // context for glDrawElements to read from it (done via Mesh::bind()).
    glVertexArrayElementBuffer(vaoId, eboId);
    /* glBindVertexArray(vaoId); */
    /* bindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); */
    glDrawElements(primitiveMode, count, GL_UNSIGNED_INT, nullptr);
    /* glBindVertexArray(0); */
}

}