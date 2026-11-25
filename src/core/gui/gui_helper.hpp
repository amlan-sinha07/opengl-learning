#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <concepts>
#include <utility>

struct gui_config {
    GLFWwindow *window = nullptr;
    const char *GLSL_version = "#version 450 core";
    float font_scale = 1.0f;

    [[nodiscard]]auto is_valid() noexcept -> bool;
};

namespace gui_helper {
void guiInit(gui_config &config);

template <typename Arg, std::invocable<Arg> ExternalDraw>
void guiRender(ExternalDraw &&draw_this, Arg &&config) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    std::forward<ExternalDraw>(draw_this)(std::forward<Arg>(config));

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void guiShutdown();
}