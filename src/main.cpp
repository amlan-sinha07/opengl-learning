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

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

int main()
{
    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans= glm::mat4(1.0f);
    glm::mat4 trans1 = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
    vec = trans1*vec;
    std::cout 
    << vec.x << " "
    << vec.y << " "
    << vec.z << " "
    << vec.w << " "
    << std::endl;
    glm::mat4 trans2 = glm::rotate(
        trans,
        glm::radians(90.0f),
        glm::vec3(0.0f,0.0f,1.0f)
    );
    vec = trans2 * vec;
    std::cout
    << vec.x << " "
    << vec.y << " "
    << vec.z << " "
    << vec.w << " "
    << std::endl;
    glm::mat4 trans3 = glm::scale(
        trans,
        glm::vec3(0.5f,0.5f,0.5f)
    );
    vec =trans3 *vec;
    std::cout 
    << vec.x << " "
    << vec.y << " "
    << vec.z << " "
    << vec.w << " "
    << std::endl;

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
        KERROR("Error: %s", e.what());

        return 1;
    }

    return 0;
}