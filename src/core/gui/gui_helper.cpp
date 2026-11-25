#include "gui_helper.hpp"
#include "../logging/logger.hpp"

[[nodiscard]] auto gui_config::is_valid() noexcept -> bool {
    return window != nullptr && GLSL_version != nullptr && GLSL_version[0] != '\0' &&
           font_scale > 0.0f;
}

namespace gui_helper {

void guiInit(gui_config &config) {

    if (!config.is_valid()) {
        KFATAL("given config is not valid");
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    io.FontGlobalScale = config.font_scale;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(config.window, true);
    ImGui_ImplOpenGL3_Init(config.GLSL_version);
}

void guiShutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

}