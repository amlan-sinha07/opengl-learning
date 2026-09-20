#include <glad/gl.h>

#include "core/window.hpp"
#include "core/debug.hpp"
#include "core/logger.hpp"

#include "renderer/shader.hpp"
#include "renderer/vertex.hpp"
#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"

#include <iostream>
#include <vector>
#include <exception>

int main()
{
    try
    {
        Window window(800, 600, "OpenGL Learning Project");

        KINFO("Opengl Initialized");
        Shader shader(
            "shaders/vertex.glsl",
            "shaders/fragment.glsl"
        );

        std::vector<Vertex> vertices{
{ -0.5f, -0.5f, 0.0f,
   1.0f, 0.0f, 0.0f,   // red
   0.0f, 0.0f },

{  0.5f, -0.5f, 0.0f,
   0.0f, 1.0f, 0.0f,   // green
   1.0f, 0.0f },

{  0.5f,  0.5f, 0.0f,
   0.0f, 0.0f, 1.0f,   // blue
   1.0f, 1.0f },

{ -0.5f,  0.5f, 0.0f,
   1.0f, 1.0f, 0.0f,   // yellow
   0.0f, 1.0f }
        };

        std::vector<unsigned int> indices{
            0, 1, 2,
            2, 3, 0
        };

        Mesh rectangle(vertices, indices);

        Renderer renderer;

        while (!window.shouldClose())
        {
            renderer.clear();

            renderer.draw(rectangle, shader);

            window.swapBuffers();
            window.pollEvents();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: "
                  << e.what()
                  << '\n';

        return 1;
    }

    return 0;
}