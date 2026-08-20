#include "example_menu.h"
#include "imgui.h"

void DrawExampleMenu() {
    ImGui::SetNextWindowSize(ImVec2(420, 320), ImGuiCond_FirstUseEver);
    ImGui::Begin("Mod Menu", nullptr, ImGuiWindowFlags_NoCollapse);

    if (ImGui::BeginTabBar("##tabs")) {

        if (ImGui::BeginTabItem("Player")) {
            static bool godMode = false;
            static bool infiniteAmmo = false;
            static float speedMultiplier = 1.0f;
            static float health = 100.0f;

            ImGui::Checkbox("God Mode", &godMode);
            ImGui::Checkbox("Infinite Ammo", &infiniteAmmo);
            ImGui::SliderFloat("Speed Multiplier", &speedMultiplier, 0.1f, 5.0f);
            ImGui::SliderFloat("Health", &health, 0.0f, 100.0f);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Visuals")) {
            static bool espEnabled = false;
            static bool showFps = true;
            static float fov = 90.0f;
            static ImVec4 espColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

            ImGui::Checkbox("ESP Enabled", &espEnabled);
            ImGui::Checkbox("Show FPS Counter", &showFps);
            ImGui::SliderFloat("FOV", &fov, 60.0f, 130.0f);
            ImGui::ColorEdit4("ESP Color", (float*)&espColor);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Settings")) {
            static int toggleKey = 0;
            const char* keys[] = { "F10", "Insert", "Home", "F1" };

            ImGui::Combo("Toggle Key", &toggleKey, keys, IM_ARRAYSIZE(keys));
            ImGui::TextWrapped("Note: changing this here doesn't rebind it live yet - it's just a placeholder control.");

            if (ImGui::Button("Reset to Defaults")) {
                // hook up reset logic here later
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::Separator();
    ImGui::TextDisabled("Example menu - replace with your own tabs/controls");

    ImGui::End();
}