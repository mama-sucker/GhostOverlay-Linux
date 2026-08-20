# Overlay

A transparent, click-through OpenGL overlay rendered with **ImGui + GLFW**, designed to sit on top of any monitor in your multi-monitor setup.

## Features

- **Transparent framebuffer** — the overlay window is fully see-through, showing whatever is behind it.
- **Click-through** — mouse events pass through the overlay by default; press **F10** to toggle an interactive ImGui menu.
- **Multi-monitor support** — select which monitor to render on via `--monitor <index>` or list all with `--list-monitors`.
- **Floating, undecorated window** — always-on-top, no title bar or resize handles.
- **Example mod menu** — pre-built ImGui tabs (Player, Visuals, Settings) as a starting point.

## Dependencies

| Package | Purpose |
|---------|---------|
| CMake ≥ 3.10 | Build system |
| OpenGL | Rendering backend |
| GLFW3 | Windowing & input |
| X11, Xfixes, Xext | Linux window management & click-through |
| ImGui (bundled) | Immediate-mode GUI |

Install on Ubuntu/Debian:

```bash
sudo apt install build-essential cmake libgl1-mesa-dev libglfw3-dev libx11-dev libxfixes-dev libxext-dev
```

## Building

```bash
cd build
cmake ..
make
```

The resulting binary is `build/overlay`.

## Usage

```bash
./overlay                          # render on monitor 0 (primary)
./overlay --monitor 1              # render on monitor 1
./overlay --list-monitors          # list all detected monitors
```

### Hotkeys

| Key | Action |
|-----|--------|
| **F10** | Toggle the ImGui menu (click-through disabled while menu is open) |

## Project Structure

```
CMakeLists.txt          # CMake build configuration
README.md               # This file
.gitignore

src/
  main.cpp              # Entry point — window creation, ImGui init, render loop
  menu/
    example_menu.cpp    # Example ImGui mod menu
    example_menu.h
  monitor/
    overlay_monitor.cpp # Monitor detection & geometry helpers
    overlay_monitor.h
external/imgui/         # ImGui source (bundled)
```

## How It Works

1. **Monitor selection** — `glfwGetMonitors` enumerates all displays; the user picks one by index.
2. **Transparent window** — `GLFW_TRANSPARENT_FRAMEBUFFER` + `GLFW_FLOATING` create a see-through, always-on-top window.
3. **Click-through** — `XFixesSetWindowShapeRegion` with an empty region tells the X server to ignore all mouse input.
4. **Menu toggle** — Pressing F10 enables click-through to be disabled so the ImGui menu is interactive. Pressing F10 again restores click-through.

## Customisation

The example menu in `example_menu.cpp` is a starting point. Replace its contents with your own ImGui widgets, tabs, or hooks. The overlay renders every frame unconditionally — integrate your game/overlay logic inside the main loop in `main.cpp`.


