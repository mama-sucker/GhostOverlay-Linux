#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_X11
#include <GLFW/glfw3native.h>

#include <X11/Xlib.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "monitor/overlay_monitor.h"
#include "menu/example_menu.h"

static bool menu_visible = false;

// Make the window ignore mouse input entirely (click-through)
void SetClickThrough(GLFWwindow* window, bool enable) {
    Display* display = glfwGetX11Display();
    Window win = glfwGetX11Window(window);

    if (enable) {
        XRectangle rect = {0, 0, 0, 0};
        XserverRegion region = XFixesCreateRegion(display, &rect, 1);
        XFixesSetWindowShapeRegion(display, win, ShapeInput, 0, 0, region);
        XFixesDestroyRegion(display, region);
    } else {
        XFixesSetWindowShapeRegion(display, win, ShapeInput, 0, 0, 0);
    }
}



int main(int argc, char** argv) {
    int targetMonitorIndex = 0;

    // Parse --monitor N
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--monitor") == 0 && i + 1 < argc) {
            targetMonitorIndex = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "--list-monitors") == 0) {
            glfwInit();
            ListMonitors();
            glfwTerminate();
            return 0;
        }
    }

    glfwInit();

    ListMonitors();
    GLFWmonitor* targetMonitor = GetTargetMonitor(targetMonitorIndex);

    int mx, my, mw, mh;
    GetMonitorGeometry(targetMonitor, mx, my, mw, mh);
    printf("Using monitor %d -> pos=(%d,%d) size=%dx%d\n", targetMonitorIndex, mx, my, mw, mh);

    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(mw, mh, "Overlay", nullptr, nullptr);
    glfwSetWindowPos(window, mx, my);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    SetClickThrough(window, true);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Toggle menu with Insert key
        static bool was_pressed = false;
        if (glfwGetKey(window, GLFW_KEY_F10) == GLFW_PRESS) {
            if (!was_pressed) {
                menu_visible = !menu_visible;
                SetClickThrough(window, !menu_visible);
            }
            was_pressed = true;
        } else {
            was_pressed = false;
        }


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Always-visible status label, top-left corner
        {
            ImGui::SetNextWindowPos(ImVec2(5, 5));
            ImGui::SetNextWindowBgAlpha(0.35f);
            ImGuiWindowFlags flags =
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoInputs |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_AlwaysAutoResize;

            ImGui::Begin("##status_label", nullptr, flags);
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "Menu Loader Active");
            ImGui::Text("F10 to toggle");
            ImGui::End();
        }

        if (menu_visible) {
            DrawExampleMenu();

        }

        ImGui::Render();
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}