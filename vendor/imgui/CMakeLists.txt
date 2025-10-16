# Good lord, CMake is a nightmare
# Had to resort to GPT for this. Probably the only valid usecase of AI, to generate CMake slop

cmake_minimum_required(VERSION 3.10)
project(imgui)

set(IMGUI_SOURCES
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_sdl3.cpp
    imgui_impl_vulkan.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

add_library(imgui::imgui ALIAS imgui)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(imgui
    Vulkan::Vulkan
    SDL3::SDL3
)

target_compile_features(imgui PRIVATE cxx_std_17)
