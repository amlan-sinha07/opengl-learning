#include "debug.hpp"
#include "../logging/logger.hpp"

#include <iostream>

namespace
{
    [[nodiscard]]
    auto sourceToString(GLenum source) -> std::string_view
    {
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            return "API";

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "Window System";

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "Shader Compiler";

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "Third Party";

        case GL_DEBUG_SOURCE_APPLICATION:
            return "Application";

        default:
            return "Other";
        }
    }

    [[nodiscard]]
    auto typeToString(GLenum type) -> std::string_view
    {
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            return "Error";

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "Deprecated Behavior";

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "Undefined Behavior";

        case GL_DEBUG_TYPE_PORTABILITY:
            return "Portability";

        case GL_DEBUG_TYPE_PERFORMANCE:
            return "Performance";

        case GL_DEBUG_TYPE_MARKER:
            return "Marker";

        default:
            return "Other";
        }
    }

    [[nodiscard]]
    auto severityToString(GLenum severity) -> std::string_view
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            return "High";

        case GL_DEBUG_SEVERITY_MEDIUM:
            return "Medium";

        case GL_DEBUG_SEVERITY_LOW:
            return "Low";

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "Notification";

        default:
            return "Unknown";
        }
    }

    [[nodiscard]]
    auto errorToString(GLenum error) -> std::string_view
    {
        switch (error)
        {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";

        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";

        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";

        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";

        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";

        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";

        default:
            return "Unknown GL error";
        }
    }
}

bool GLErrorHandler::init()
{
    glEnable(GL_DEBUG_OUTPUT);

    // Useful while debugging
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(
        debugCallback,
        nullptr
    );

    glDebugMessageControl(
        GL_DONT_CARE,
        GL_DONT_CARE,
        GL_DONT_CARE,
        0,
        nullptr,
        GL_TRUE
    );
}

void GLErrorHandler::clearErrors()
{
    constexpr int MAX_DRAIN = 64;

    for (int i = 0; i < MAX_DRAIN; ++i) {
        if (glGetError() == GL_NO_ERROR) {
            break;
        }
    }
}

auto GLErrorHandler::checkErrors(
    std::string_view expr,
    std::string_view file,
    int line
) -> bool
{
    bool ok = true;

    constexpr int MAX_ERRORS = 16;
    int errorsFound = 0;

    while (errorsFound < MAX_ERRORS)
    {
        GLenum error = glGetError();

        if (error == GL_NO_ERROR)
        {
            break;
        }

        KERROR(
            "[OpenGL Error] %s (%#x)"
            "\n    at: %s"
            "\n    in: %s:%d",
            errorToString(error).data(),
            error,
            expr.data(),
            file.data(),
            line
        );

        ok = false;
        ++errorsFound;
    }

    return ok;
}

void GLAPIENTRY GLErrorHandler::debugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    [[maybe_unused]] GLsizei length,
    const GLchar* message,
    [[maybe_unused]] const void* userParam
)
{
    const char* typeText = typeToString(type).data();
    const char* sourceText = sourceToString(source).data();
    const char* severityText = severityToString(severity).data();
    const char* payload = "[GL Debug] {%u} %s | source: %s | severity: %s\n    %s";

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        KERROR(payload, id, typeText, sourceText, severityText, message);
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
    case GL_DEBUG_SEVERITY_LOW:
        KWARN(payload, id, typeText, sourceText, severityText, message);
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        KINFO(payload, id, typeText, sourceText, severityText, message);
        break;

    default:
        KDEBUG(payload, id, typeText, sourceText, severityText, message);
        break;
    }
}