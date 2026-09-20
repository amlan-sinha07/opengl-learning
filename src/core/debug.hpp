#pragma once

#include <glad/gl.h>
#include <string_view>
#include <iostream>

class GLErrorHandler {
    public:
    GLErrorHandler() = delete;
    
    static void init();

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
//Windows MSVC present
#if defined(_MSC_VER)
    #define GL_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #define GL_BREAK() __builtin_trap()
#else
    #define GL_BREAK() ((void)0)
#endif
 
#ifdef NDEBUG
    #define GL_CALL(expr) expr
#else
    #define GL_CALL(expr) \
        do { \
            GLErrorHandler::clearErrors(); \
            expr; \
            if (!GLErrorHandler::checkErrors(#expr, __FILE__, __LINE__)) { \
            } \
        } while (0)
#endif