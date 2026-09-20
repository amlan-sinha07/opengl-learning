#pragma once

#define GLFW_INCLUDE_NONE

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Application {
private:
    GLFWwindow* m_window{nullptr};
    int m_width;
    int m_height;
    const char* m_title;

public:
    Application(
        int width = 800,
        int height = 600,
        const char* title = "OpenGL Project"
    );

    ~Application();

    void run();

private:
    void init();
    void processInput();
    void update();
    void render();
};