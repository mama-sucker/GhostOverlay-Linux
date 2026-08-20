#pragma once
#include <X11/Xlib.h>

// Call once after creating your GLFW window/X11 display.
void InitHotkeyPolling(Display* display, int keysym);

// Call once per frame. Returns true exactly once per press (edge-triggered).
bool PollGlobalHotkey();