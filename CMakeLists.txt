cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(GhostOverlay LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

add_executable(GhostOverlay
    src/main.cpp
    src/monitor/overlay_monitor.cpp
    src/menu/example_menu.cpp
    src/hotkey/hotkey.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(GhostOverlay PRIVATE
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${GLFW_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(GhostOverlay PRIVATE
    ${GLFW_LIBRARIES}
    OpenGL::GL
    X11
    Xfixes
    Xext
)

target_compile_options(GhostOverlay PRIVATE ${GLFW_CFLAGS_OTHER})

set(CMAKE_OUTPUT_NAME "GhostOverlay")


