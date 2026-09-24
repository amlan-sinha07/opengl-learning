#pragma once

#include <glad/gl.h>
#include <string_view>
#include <cassert>

class GLErrorHandler {
    public:
    GLErrorHandler() = delete;
    
    [[nodiscard]] static auto init() -> bool;

    static void clearErrors();
    [[nodiscard]] static auto checkErrors(std::string_view expr, std::string_view file, int line) ->bool;

    private:
        static void GLAPIENTRY debugCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam
    );
};
// got tired of GL_CALL breaking
#define GL_SWEEP(label)                                                                          \
    do {                                                                                         \
        [[maybe_unused]] const bool ok = GLErrorHandler::checkErrors(label, __FILE__, __LINE__); \
        assert(ok);                                                                              \
        GLErrorHandler::clearErrors();                                                           \
    } while (0)