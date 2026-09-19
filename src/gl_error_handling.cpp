#include "gl_error_handling.hpp"

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

void GLErrorHandler::init()
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
    while (glGetError() != GL_NO_ERROR)
    {
        
    }
}

auto GLErrorHandler::checkErrors(
    std::string_view expr,
    std::string_view file,
    int line
) -> bool
{
    bool ok = true;

    while (GLenum error = glGetError())
    {
        std::cerr
            << "[OpenGL Error] "
            << errorToString(error)
            << " (0x"
            << std::hex
            << error
            << std::dec
            << ")\n"
            << "    at: "
            << expr
            << '\n'
            << "    in: "
            << file
            << ':'
            << line
            << '\n';

        ok = false;
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
    std::cerr
        << "[GL Debug] {"
        << id
        << "} "
        << typeToString(type)
        << " | source: "
        << sourceToString(source)
        << " | severity: "
        << severityToString(severity)
        << '\n'
        << "    "
        << message
        << '\n';

    if (severity == GL_DEBUG_SEVERITY_HIGH)
    {
        GL_BREAK();
    }
}