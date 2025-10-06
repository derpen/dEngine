cmake_minimum_required(VERSION 3.16)
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

# vkbootstrap
add_library(vkbootstrap STATIC)
file(GLOB_RECURSE vkbootstrap_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
vendor/vk-bootstrap/*)
target_sources(vkbootstrap PUBLIC 
  ${vkbootstrap_src}
  )
target_include_directories(vkbootstrap PUBLIC vendor/vk-bootstrap)
target_link_libraries(vkbootstrap PUBLIC Vulkan::Vulkan $<$<BOOL:UNIX>:${CMAKE_DL_LIBS}>)

# stb
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE vendor/stb_image)
target_link_libraries(dEngine INTERFACE stb_image)

# Imgui
file(GLOB_RECURSE imgui_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
vendor/imgui/*)
add_library(imgui STATIC)
target_include_directories(imgui PUBLIC vendor/imgui)
target_sources(imgui PUBLIC
${imgui_src}
)
target_link_libraries(dEngine INTERFACE imgui)

# Vulkan Memory Allocator
add_library(vma INTERFACE)
target_include_directories(vma INTERFACE vendor/VulkanMemoryAllocator)
target_link_libraries(dEngine INTERFACE vma)

include_directories(include)

target_link_libraries(dEngine PRIVATE 
SDL3::SDL3
vk-bootstrap::vk-bootstrap
fmt::fmt
fastgltf::fastgltf
glm::glm
)
