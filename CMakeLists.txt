cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20) # C++ 20. I know, pretty cringe
project(dEngine)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file(GLOB_RECURSE src_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
src/* include/*
)

find_package(Vulkan REQUIRED)

add_executable(dEngine WIN32 ${src_files})

# External libraries
add_subdirectory(vendor/vk-bootstrap)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/fastgltf)
add_subdirectory(vendor/glm)

# stb
include_directories(vendor/stb_image)

## FIX ME FIX ME FIX ME FIX ME FIX ME FIX ME FIX ME FIX ME FIX ME FIX ME 
# Imgui
#file(GLOB_RECURSE imgui_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#vendor/imgui/*)
#add_library(imgui STATIC)
#target_include_directories(imgui PUBLIC vendor/imgui)
#target_sources(imgui PUBLIC
#${imgui_src}
#)
#target_link_libraries(dEngine INTERFACE imgui)


# Vulkan Memory Allocator
include_directories(vendor/VulkanMemoryAllocator/include)

include_directories(include)

target_link_libraries(dEngine PRIVATE 
SDL3::SDL3
vk-bootstrap::vk-bootstrap
fmt::fmt
Vulkan::Vulkan
fastgltf::fastgltf
glm::glm
)
