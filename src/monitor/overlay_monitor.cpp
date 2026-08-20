#include "overlay_monitor.h"
#include <cstdio>

void ListMonitors() {
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    printf("Detected %d monitor(s):\n", count);
    for (int i = 0; i < count; i++) {
        int xpos, ypos, width, height;
        glfwGetMonitorWorkarea(monitors[i], &xpos, &ypos, &width, &height);
        const char* name = glfwGetMonitorName(monitors[i]);
        printf("  [%d] %s  pos=(%d,%d) size=%dx%d\n", i, name, xpos, ypos, width, height);
    }
}

GLFWmonitor* GetTargetMonitor(int index) {
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);

    if (index < 0 || index >= count) {
        printf("Warning: monitor index %d out of range (0-%d), defaulting to 0\n", index, count - 1);
        index = 0;
    }
    return monitors[index];
}

void GetMonitorGeometry(GLFWmonitor* monitor, int& mx, int& my, int& mw, int& mh) {
    glfwGetMonitorWorkarea(monitor, &mx, &my, &mw, &mh);
}