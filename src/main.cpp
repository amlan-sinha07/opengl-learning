#include <glad/gl.h>

#include "platform/window.hpp"
#include "core/debugging/debug.hpp"
#include "core/logging/logger.hpp"

#include "renderer/shader/shader.hpp"
#include "renderer/mesh/vertex.hpp"
#include "renderer/mesh/mesh.hpp"
#include "renderer/rendering/renderer.hpp"

#include <iostream>
#include <vector>
#include <exception>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans= glm::mat4(1.0f);
    trans = glm::translate(
        trans,
        glm::vec3(1.0f,1.0f,0.0f)
    );
    trans = glm::rotate(
        trans,
        glm::radians(90.0f),
        glm::vec3(0.0f,0.0f,1.0f)
    );
    trans = glm::scale(
        trans,
        glm::vec3(0.5f,0.5f,0.5f)
    );
    vec = vec * trans ;
    std::cout 
        << vec.x <<"\t"
        << vec.y <<"\t"
        << vec.z <<"\t" 
        << vec.w <<std::endl;

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
                0.0f, 0.0f 
            },

            {  0.5f, -0.5f, 0.0f,
                0.0f, 1.0f, 0.0f,   // green
                1.0f, 0.0f 
            },

            {  0.5f,  0.5f, 0.0f,
                0.0f, 0.0f, 1.0f,   // blue
                1.0f, 1.0f 
            },

            { -0.5f,  0.5f, 0.0f,
                1.0f, 1.0f, 0.0f,   // yellow
                0.0f, 1.0f 
            }
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
        KERROR("Error: %s", e.what());

        return 1;
    }

    return 0;
}