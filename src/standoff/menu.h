bool running = true;

void RenderMenu() {
    ImGui::Checkbox("box", &esp_enabled);
    ImGui::ColorEdit4("color", (float*)&esp_box_color);
    
    if(ImGui::Checkbox("running", &running)) {
        if(!running) {
            exit(0);
        }
    }

    g_window = ImGui::GetCurrentWindow();
    ImGui::End();
}
