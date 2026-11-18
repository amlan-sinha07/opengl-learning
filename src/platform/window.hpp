#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *m_window{nullptr};
    GLFWmonitor *m_monitor{nullptr};
    int m_width;
    int m_height;
    /* todo will put these to use later */
    int m_areaX, m_areaY, m_areaW, m_areaH;
    static constexpr unsigned int VERSION_MAJOR = 4, VERSION_MINOR = 5;
    static void glfwErrorCallback(int error, const char *description);

    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

    static void processWindowInput(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
    Window(int width, int height, const char *title);
    ~Window();

    Window(const Window &) = delete;
    auto operator=(const Window &) -> Window & = delete;

    Window(Window &&) noexcept;
    auto operator=(Window &&) noexcept -> Window &;

    [[nodiscard]] bool shouldClose() const;

    void swapBuffers() const;
    void pollEvents() const;

    [[nodiscard]]
    auto getNativeWindow() const -> GLFWwindow *;

    [[nodiscard]]
    auto getWidth() const -> int;

    [[nodiscard]]
    auto getHeight() const -> int;
};