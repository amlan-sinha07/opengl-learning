#include <glad/gl.h>

#include "Window.hpp"

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
        self->m_width_ = width;
        self->m_height_ = height;
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
    : m_width_(width),
      m_height_(height)
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
    m_window_ = glfwCreateWindow(
        m_width_,
        m_height_,
        title,
        nullptr,
        nullptr
    );

    if (!m_window_)
    {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return;
    }

    // ----------------
    // Make OpenGL context current
    // ----------------
    glfwMakeContextCurrent(m_window_);

    // ----------------
    // Initialize GLAD
    // ----------------
    if (!gladLoadGL(
            (GLADloadfunc)glfwGetProcAddress))
    {
        std::cerr << "GLAD initialization failed\n";

        glfwDestroyWindow(m_window_);
        glfwTerminate();

        m_window_ = nullptr;

        return;
    }

    // ----------------
    // Initial framebuffer size
    // ----------------
    int framebufferWidth;
    int framebufferHeight;

    glfwGetFramebufferSize(
        m_window_,
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
        m_window_,
        this
    );

    // ----------------
    // Register resize callback
    // ----------------
    glfwSetFramebufferSizeCallback(
        m_window_,
        framebufferSizeCallback
    );
}

Window::~Window()
{
    if (m_window_)
    {
        glfwDestroyWindow(m_window_);
    }

    glfwTerminate();
}

bool Window::shouldClose() const
{
    return m_window_ == nullptr ||
           glfwWindowShouldClose(m_window_);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(m_window_);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

GLFWwindow* Window::getNativeWindow() const
{
    return m_window_;
}

int Window::getWidth() const
{
    return m_width_;
}

int Window::getHeight() const
{
    return m_height_;
}