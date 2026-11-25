#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_XYZW_ONLY

#include <glad/gl.h>

#include "platform/window.hpp"
#include "core/debugging/debug.hpp"
#include "core/logging/logger.hpp"

#include "core/gui/gui_helper.hpp"
#include "core/debugging/debugging_ui.hpp"

#include "renderer/shader/shader.hpp"
#include "renderer/mesh/vertex.hpp"
#include "renderer/mesh/mesh.hpp"
#include "renderer/rendering/renderer.hpp"

#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
// uncomment to turn off debug
// #define NDEBUG

auto main() -> int {
#ifdef NDEBUG
    Log::setLevel(Log::Level::Info);
#else
    Log::setLevel(Log::Level::Trace);
#endif
    // not really required as we are using set level
    // Log::initFromEnv();

    // KFATAL("Starting OpenGL Learning");
    KERROR("Starting OpenGL Learning");
    KWARN("Starting OpenGL Learning");
    KINFO("Starting OpenGL Learning");
    KDEBUG("Starting OpenGL Learning");
    KTRACE("Starting OpenGL Learning");

    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    auto trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    KINFO("matrix for trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)), is of length {} and of values {}",trans.length(),glm::to_string(trans));
    vec = trans * vec;
    KINFO("vector for vec = trans * vec, is T({},{},{},{})",vec.x,vec.y,vec.z,vec.w);

    try {
        Window window(800, 600, "OpenGL Learning Project");
        KINFO("Window and OpenGL context initialized");

        Shader shader("shaders/vertex.vert", "shaders/fragment.frag");

        if (0 == shader.getId()) {
            KERROR("Shader program initialization failed");
            return 1;
        }

        KINFO("Shader program initialized");

        std::vector<MeshVertex> Vertices{
            // (n:even)position   // (n+1:odd)color
            {.Position = glm::vec3{-0.5F, -0.5F, 0.0F},
             .Color = glm::vec3{1.0F, 0.0F, 0.0F} /* , .Normal=glm::vec3{0.0F, 0.0F, 0.0F} */},  // red
            {.Position = glm::vec3{0.5F, -0.5F, 0.0F},
             .Color = glm::vec3{0.0F, 0.0F, 1.0F} /* , .Normal=glm::vec3{0.0F, 0.0F, 0.0F} */},  // blue
            {.Position = glm::vec3{0.5F, 0.5F, 0.0F},
             .Color = glm::vec3{0.0F, 1.0F, 0.0F} /* , .Normal=glm::vec3{0.0F, 0.0F, 0.0F} */},  // green
            {.Position = glm::vec3{-0.5F, 0.5F, 0.0F},
             .Color = glm::vec3{1.0F, 1.0F,0.0F} /* , .Normal=glm::vec3{0.0F, 0.0F, 0.0F} */},  // yellow
        };

        std::vector<unsigned int> Indices{0, 1, 2, 2, 3, 0};

        KINFO("Creating demo mesh");
        Mesh rectangle(Vertices, Indices);
        Mesh movedRectangle{std::move(rectangle)};
        // tested works
        // Window movedWindow(std::move(window));
        Renderer renderer;
        KINFO("Renderer initialized");

        renderer.clear_color({0.5f, 0.5f, 0.5f, 1.0f});

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glm::vec3 baseScale{1.0F, 1.0F, 1.0F};
        glm::vec3 pulseScale{1.5F, 1.5F, 1.5F};
        
        std::vector<MeshVertex> animatedVertices;
        animatedVertices.reserve(Vertices.size());

        gui_config config;
        config.window=window.getNativeWindow();

        double now = 0.0F;
        // double last_frame_time = 0.0F
        gui_helper::guiInit(config);

        while (true) {

            if (0 != window.shouldClose()) {
                break;
            }

            window.pollEvents();
            now = glfwGetTime();
            double pulse = (std::sin(now) + 1.0F) * 0.5F;
            glm::vec3 currentScale = glm::mix(baseScale, pulseScale, static_cast<float>(pulse));

            animatedVertices.clear();
            for (const auto &v : Vertices) {
                animatedVertices.push_back({.Position = v.Position * currentScale,
                                            .Color = v.Color /* , .Normal=v.Normal */});
            }

            movedRectangle.updateVertices(animatedVertices);

            renderer.clear_bits(GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT);

            shader.use();
            shader.setMat4("uMVP", glm::mat4(1.0f));
            renderer.draw(movedRectangle, shader);
            gui_helper::guiRender(testFrame, config);

            window.swapBuffers();
        }
        gui_helper::guiShutdown();

        KINFO("Application stopped");
    } catch (const std::exception &Err) {
        KERROR("Error: {}", Err.what());

        return 1;
    }

    return 0;
}
