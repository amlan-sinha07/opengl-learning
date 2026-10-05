#pragma once

#include <glad/gl.h>
#include <string_view>
#include <cassert>
#include "../logging/logger.hpp"

class GLErrorHandler {
public:
    GLErrorHandler() = delete;

    static auto init() -> void;

    static void clearErrors();
    [[nodiscard]] static auto checkErrors(std::string_view expr, std::string_view file, int line)
        -> bool;

private:
    static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                         GLsizei length, const GLchar *message,
                                         const void *userParam);
};
// got tired of GL_CALL breaking
#define GL_SWEEP(label)                                                         \
    do {                                                                        \
        const bool ok = GLErrorHandler::checkErrors(label, __FILE__, __LINE__); \
        KASSERT(ok, "OpenGL call reported an error");                           \
        GLErrorHandler::clearErrors();                                          \
    } while (false)
