#pragma once
#include <GLFW/glfw3.h>

// Prints all detected monitors with index, name, position, and size
void ListMonitors();

// Returns the GLFWmonitor* for a given index, or nullptr if out of range.
// Falls back to primary monitor (index 0) with a warning if invalid.
GLFWmonitor* GetTargetMonitor(int index);

// Fills mx, my, mw, mh with the work area (position + size) of the given monitor
void GetMonitorGeometry(GLFWmonitor* monitor, int& mx, int& my, int& mw, int& mh);