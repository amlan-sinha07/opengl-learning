#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* m_window{nullptr};
    int m_width;
    int m_height;
    static void glfwErrorCallback(int error, const char* description);

    static void framebufferSizeCallback(
        GLFWwindow* window,
        int width,
        int height
    );

public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;


    [[nodiscard]] bool shouldClose() const;

    void swapBuffers() const;
    void pollEvents() const;

    [[nodiscard]]
    GLFWwindow* getNativeWindow() const;

    [[nodiscard]]
    int getWidth() const;

    [[nodiscard]]
    int getHeight() const;
};