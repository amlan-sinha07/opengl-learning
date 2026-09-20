#include "Application.hpp"
#include <glad/gl.h>
#include <iostream>
#include <stdexcept>
Application::Application(int width,int height,
                        const char* title)
    :   m_window(nullptr),
        m_width(width),
        m_height(height),
        m_title(title)
{
    init();
}
Application::~Application()
{
    if (m_window){
        glfwDestroyWindow(m_window);
    }
    glfwTerminate;
}
void Application::init()
{
    if (!glfwInit()){
        throw std::runtime_error("Failed to initialize GLFW");
    }
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

m_window = glfwCreateWindow(
    m_width,
    m_height,
    m_title,
    nullptr,
    nullptr
);

if (m_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
}

glfwMakeContextCurrent(m_window);
}