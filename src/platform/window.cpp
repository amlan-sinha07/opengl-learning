#include <glad/gl.h>

#include "window.hpp"
#include "../core/logging/logger.hpp"

void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    KINFO("Framebuffer resized: {}x{}", width, height);

    auto *self = static_cast<Window *>(glfwGetWindowUserPointer(window));

    if (self) {
        self->m_width = width;
        self->m_height = height;
    }
}
void Window::glfwErrorCallback(int error, const char *description) {
    KERROR("[GLFW Error] ({}) {}", error, description);
}

Window::Window(int width, int height, const char *title)
    : m_monitor(glfwGetPrimaryMonitor()), m_width(width), m_height(height), m_areaX(0), m_areaY(0),
      m_areaW(0), m_areaH(0) {
    glfwSetErrorCallback(glfwErrorCallback);
    glfwGetMonitorWorkarea(m_monitor, &m_areaX, &m_areaY, &m_areaW, &m_areaH);
    // ----------------
    // Initialize GLFW
    // ----------------
    if (!glfwInit()) {
        KERROR("GLFW initialization failed");
        return;
    }

    KINFO("GLFW initialized");

    // ----------------
    // OpenGL version
    // ----------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // ----------------
    // Create window
    // ----------------

    m_window = glfwCreateWindow(m_width, m_height, title, m_monitor, nullptr);

    if (!m_window) {
        KERROR("Window creation failed");
        glfwTerminate();
        return;
    }

    KINFO("Window created: {}x{}", m_width, m_height);

    // ----------------
    // Make OpenGL context current
    // ----------------
    glfwMakeContextCurrent(m_window);
    KINFO("OpenGL context is current");

    // ----------------
    // Initialize GLAD
    // ----------------
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        KERROR("GLAD initialization failed");

        glfwDestroyWindow(m_window);
        glfwTerminate();

        m_window = nullptr;

        return;
    }

    KINFO("GLAD initialized");

    // ----------------
    // Initial framebuffer size
    // ----------------
    int framebufferWidth{0};
    int framebufferHeight{0};

    glfwGetFramebufferSize(m_window, &framebufferWidth, &framebufferHeight);

    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // ----------------
    // Give GLFW access
    // to this Window object
    // ----------------
    glfwSetWindowUserPointer(m_window, this);

    // ----------------
    // Register resize callback
    // ----------------
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
}

Window::~Window() {
    KINFO("Destroying window");

    if (m_window) {
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

bool Window::shouldClose() const { return m_window == nullptr || glfwWindowShouldClose(m_window); }

void Window::swapBuffers() const { glfwSwapBuffers(m_window); }

void Window::pollEvents() const { glfwPollEvents(); }

GLFWwindow *Window::getNativeWindow() const { return m_window; }

int Window::getWidth() const { return m_width; }

int Window::getHeight() const { return m_height; }