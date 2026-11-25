#include "debugging_ui.hpp"

void testFrame(gui_config &config) {
    // newframe called

    ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

    ImGui::TextUnformatted("This is some useful unformatted text.");    // Display some text (you can use a format strings too)

    ImGui::SliderFloat("font_size", &config.font_scale, 1.0f, 10.0f);

    ImGui::SetWindowFontScale(config.font_scale);

    ImGui::End();

    // render called
}