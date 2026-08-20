#include "hotkey.h"
#include <X11/keysym.h>

static Display* g_display = nullptr;
static int g_keycode = 0;
static bool g_was_down = false;

void InitHotkeyPolling(Display* display, int keysym) {
    g_display = display;
    g_keycode = XKeysymToKeycode(display, keysym);
}

bool PollGlobalHotkey() {
    if (!g_display) return false;

    char keymap[32];
    XQueryKeymap(g_display, keymap);

    bool is_down = (keymap[g_keycode / 8] & (1 << (g_keycode % 8))) != 0;

    bool triggered = is_down && !g_was_down;
    g_was_down = is_down;

    return triggered;
}