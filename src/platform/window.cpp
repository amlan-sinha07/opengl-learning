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

void Window::processWindowInput(GLFWwindow *window, int key,[[maybe_unused]] int scancode, int action,[[maybe_unused]] int mods) {
    if (action == GLFW_REPEAT) {
        return;
    }

    switch (key) {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        break;

    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS) {
            KINFO("jump button pressed");
        } else if (action == GLFW_RELEASE) {
            KINFO("jump button released");
        }
        break;

    case GLFW_KEY_F11:
        if (action == GLFW_PRESS) {
            KINFO("fullscreen where?");
        }
        break;

    default:
        break;
    }
}

void Window::glfwErrorCallback(int error, const char *description) {
    KERROR("[GLFW Error] ({}) {}", error, description);
}

Window::Window(int width, int height, const char *title)
    : m_width(width), m_height(height), m_areaX(0), m_areaY(0), m_areaW(0), m_areaH(0) {
    glfwSetErrorCallback(glfwErrorCallback);
    // ----------------
    // Initialize GLFW
    // ----------------
    if (!glfwInit()) {
        KERROR("GLFW initialization failed");
        return;
    }

    KINFO("GLFW initialized");
    m_monitor = glfwGetPrimaryMonitor();
    if (m_monitor) {
        glfwGetMonitorWorkarea(m_monitor, &m_areaX, &m_areaY, &m_areaW, &m_areaH);
    }
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

    m_window = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);

    if (!m_window) {
        KERROR("Window creation failed");
        glfwTerminate();
        return;
    }

    if (m_monitor && m_areaW > 0 && m_areaH > 0) {
        int x = m_areaX + ((m_areaW - m_width) / 2);
        int y = m_areaY + ((m_areaH - m_height) / 2);
        glfwSetWindowPos(m_window, x, y);
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
    if (!gladLoadGL(glfwGetProcAddress)) {
        KERROR("GLAD initialization failed");

        glfwDestroyWindow(m_window);
        glfwTerminate();

        m_window = nullptr;

        return;
    }

    KINFO("GLAD initialized");

    glEnable(GL_DEPTH_TEST);

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
    glfwSetKeyCallback(m_window, processWindowInput);
}

Window::Window(Window &&other) noexcept
    : m_window(other.m_window), m_monitor(other.m_monitor), m_width(other.m_width),
      m_height(other.m_height), m_areaX(other.m_areaX), m_areaY(other.m_areaY),
      m_areaW(other.m_areaW), m_areaH(other.m_areaH) {
    other.m_window = nullptr;
    other.m_monitor = nullptr;
    other.m_width = 0;
    other.m_height = 0;
    other.m_areaX = 0;
    other.m_areaY = 0;
    other.m_areaW = 0;
    other.m_areaH = 0;
}

auto Window::operator=(Window &&other) noexcept -> Window & {
    if (this != &other) {
        // Release whatever this window currently owns before taking other's
        // resources. Without this the old GLFW window would leak.
        if (m_window) {
            KINFO("Destroying window {}", glfwGetWindowTitle(m_window));
            glfwDestroyWindow(m_window);
        }

        m_window = other.m_window;
        other.m_window = nullptr;

        m_monitor = other.m_monitor;
        other.m_monitor = nullptr;

        m_width = other.m_width;
        other.m_width = 0;

        m_height = other.m_height;
        other.m_height = 0;

        m_areaX = other.m_areaX;
        other.m_areaX = 0;

        m_areaY = other.m_areaY;
        other.m_areaY = 0;

        m_areaW = other.m_areaW;
        other.m_areaW = 0;

        m_areaH = other.m_areaH;
        other.m_areaH = 0;
    }
    return *this;
}

Window::~Window() {
    // A moved-from Window has no handle, so dont ask GLFW about a null window.
    if (m_window) {
        KINFO("Destroying window {}", glfwGetWindowTitle(m_window));
        glfwDestroyWindow(m_window);
    }

    glfwTerminate();
}

auto Window::shouldClose() const -> bool {
    return m_window == nullptr || glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() const { glfwSwapBuffers(m_window); }

void Window::pollEvents() const { glfwPollEvents(); }

auto Window::getNativeWindow() const -> GLFWwindow * { return m_window; }

auto Window::getWidth() const -> int { return m_width; }

auto Window::getHeight() const -> int { return m_height; }