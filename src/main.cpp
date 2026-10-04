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
#include <cmath>

#include "math/vector3.hpp"

auto main() -> int
{
#ifdef NDEBUG
    Log::setLevel(Log::Level::Info);
#else
    Log::setLevel(Log::Level::Debug);
#endif

    KINFO("Starting OpenGL Learning");

    Vector3 Vec3{1.0F, 0.0F, 0.0F};
    std::cout << Vec3 <<'\n';

    try
    {
        Window Window(800, 600, "OpenGL Learning Project");
        KINFO("Window and OpenGL context initialized");

        Shader Shader(
            "shaders/vertex.vert",
            "shaders/fragment.frag"
        );

        if (Shader.getId() == 0)
        {
            KERROR("Shader program initialization failed");
            return 1;
        }

        KINFO("Shader program initialized");

        std::vector<Vertex> Vertices{
            { {-0.5F, -0.5F, 0.0F}, {1.0F, 0.0F, 0.0F} },   // red
            { { 0.5F, -0.5F, 0.0F}, {0.0F, 1.0F, 0.0F} },   // green
            { { 0.5F,  0.5F, 0.0F}, {0.0F, 0.0F, 1.0F} },   // blue
            { {-0.5F,  0.5F, 0.0F}, {1.0F, 1.0F, 0.0F} },   // yellow
        };

        std::vector<unsigned int> Indices{
            0, 1, 2,
            2, 3, 0
        };

        KINFO("Creating demo mesh");
        Mesh Rectangle(Vertices, Indices);
        Renderer Renderer;
        KINFO("Renderer initialized");

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        Vector3 baseScale{1.0F, 1.0F, 1.0F};
        Vector3 pulseScale{1.5F, 1.5F, 1.5F};
        float time = 0.0F;

        while (!Window.shouldClose())
        {
            time += 0.016F;
            float pulse = (std::sin(time) + 1.0F) * 0.5F;
            Vector3 currentScale = baseScale.lerp(pulseScale, pulse);

            std::vector<Vertex> animatedVertices;
            animatedVertices.reserve(Vertices.size());
            for (const auto& v : Vertices)
            {
                animatedVertices.push_back({v.position * currentScale, v.color});
            }

            Rectangle.updateVertices(animatedVertices);

            Renderer.clear();
            Renderer.draw(Rectangle, Shader);

            Window.swapBuffers();
            Window.pollEvents();
        }

        KINFO("Application stopped");
    }
    catch (const std::exception& Err)
    {
        KERROR("Error: %s", Err.what());

        return 1;
    }

    return 0;
}
