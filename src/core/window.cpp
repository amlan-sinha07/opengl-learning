#include <glad/gl.h>

#include "window.hpp"

#include <iostream>

void Window::framebufferSizeCallback(
    GLFWwindow* window,
    int width,
    int height)
{
    glViewport(0, 0, width, height);

    Window* self =
        static_cast<Window*>(
            glfwGetWindowUserPointer(window)
        );

    if (self)
    {
        self->m_width = width;
        self->m_height = height;
    }
}
void Window::glfwErrorCallback(int error, const char* description)
{
    std::cerr << "[GLFW Error] (" << error << ") " << description << '\n';
}

Window::Window(
    int width,
    int height,
    const char* title)
    : m_width(width),
      m_height(height)
{
    glfwSetErrorCallback(glfwErrorCallback);
    // ----------------
    // Initialize GLFW
    // ----------------
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed\n";
        return;
    }

    // ----------------
    // OpenGL version
    // ----------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    glfwWindowHint(
        GLFW_OPENGL_DEBUG_CONTEXT,
        GLFW_TRUE
    );

    // ----------------
    // Create window
    // ----------------
    m_window = glfwCreateWindow(
        m_width,
        m_height,
        title,
        nullptr,
        nullptr
    );

    if (!m_window)
    {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return;
    }

    // ----------------
    // Make OpenGL context current
    // ----------------
    glfwMakeContextCurrent(m_window);

    // ----------------
    // Initialize GLAD
    // ----------------
    if (!gladLoadGL(
            (GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "GLAD initialization failed\n";

        glfwDestroyWindow(m_window);
        glfwTerminate();

        m_window = nullptr;

        return;
    }

    // ----------------
    // Initial framebuffer size
    // ----------------
    int framebufferWidth;
    int framebufferHeight;

    glfwGetFramebufferSize(
        m_window,
        &framebufferWidth,
        &framebufferHeight
    );

    glViewport(
        0,
        0,
        framebufferWidth,
        framebufferHeight
    );

    // ----------------
    // Give GLFW access
    // to this Window object
    // ----------------
    glfwSetWindowUserPointer(
        m_window,
        this
    );

    // ----------------
    // Register resize callback
    // ----------------
    glfwSetFramebufferSizeCallback(
        m_window,
        framebufferSizeCallback
    );
}

Window::~Window()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

bool Window::shouldClose() const
{
    return m_window == nullptr ||
           glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_window;
}

int Window::getWidth() const
{
    return m_width;
}

int Window::getHeight() const
{
    return m_height;
}