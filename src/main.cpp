#define GLM_ENABLE_EXPERIMENTAL
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

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/compatibility.hpp>

auto main() -> int {
#ifdef NDEBUG
    Log::setLevel(Log::Level::Info);
#else
    Log::setLevel(Log::Level::Debug);
#endif

    KINFO("Starting OpenGL Learning");

    glm::vec3 Vec3{1.0F, 0.0F, 0.0F};
    std::cout << glm::to_string(Vec3) << '\n';

    try {
        Window Window(800, 600, "OpenGL Learning Project");
        KINFO("Window and OpenGL context initialized");

        Shader Shader("shaders/vertex.vert", "shaders/fragment.frag");

        if (0 == Shader.getId()) {
            KERROR("Shader program initialization failed");
            return 1;
        }

        KINFO("Shader program initialized");

        std::vector<MeshVertex> Vertices{
            // (n:even)position   // (n+1:odd)color
            {.Position =glm::vec3{-0.5F, -0.5F, 0.0F}, .Color=glm::vec3{1.0F, 0.0F, 0.0F}, .Normal=glm::vec3{0.0F, 0.0F, 0.0F}},  // red
            {.Position=glm::vec3{0.5F, -0.5F, 0.0F}, .Color=glm::vec3{0.0F, 1.0F, 0.0F}, .Normal=glm::vec3{0.0F, 0.0F, 0.0F}},   // green
            {.Position=glm::vec3{0.5F, 0.5F, 0.0F}, .Color=glm::vec3{0.0F, 0.0F, 1.0F}, .Normal=glm::vec3{0.0F, 0.0F, 0.0F}},    // blue
            {.Position=glm::vec3{-0.5F, 0.5F, 0.0F}, .Color=glm::vec3{1.0F, 1.0F, 0.0F}, .Normal=glm::vec3{0.0F, 0.0F, 0.0F}},   // yellow
        };

        std::vector<unsigned int> Indices{0, 1, 2, 2, 3, 0};

        KINFO("Creating demo mesh");
        Mesh Rectangle(Vertices, Indices, GL_TRIANGLES);
        Renderer Renderer;
        KINFO("Renderer initialized");

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 baseScale{1.0F, 1.0F, 1.0F};
        glm::vec3 pulseScale{1.5F, 1.5F, 1.5F};
        float time = 0.0F;

        while (0 == Window.shouldClose()) {
            time += 0.05F;
            float pulse = (std::sin(time) + 1.0F) * 0.5F;
            glm::vec3 currentScale = glm::lerp(baseScale, pulseScale, pulse);

            std::vector<MeshVertex> animatedVertices;
            animatedVertices.reserve(Vertices.size());
            for (const auto &v : Vertices) {
                animatedVertices.push_back({.Position=v.Position * currentScale, .Color=v.Color, .Normal=v.Normal});
            }

            Rectangle.updateVertices(animatedVertices);

            Renderer.clear_color({0.5,0.5,0.5,1.0});
            Renderer.clear_bits(GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT);
            Renderer.draw(Rectangle, Shader);

            Window.swapBuffers();
            Window.pollEvents();
        }

        KINFO("Application stopped");
    } catch (const std::exception &Err) {
        KERROR("Error: {}", Err.what());

        return 1;
    }

    return 0;
}
