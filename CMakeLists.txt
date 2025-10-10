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

###############################
### Shaders shenanigans
###############################
#find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.comp"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/assets/shaders/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  message(STATUS COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV})
  add_custom_command(
    OUTPUT ${SPIRV}
    #COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )
###############################


target_link_libraries(dEngine PRIVATE 
SDL3::SDL3
vk-bootstrap::vk-bootstrap
fmt::fmt
Vulkan::Vulkan
fastgltf::fastgltf
glm::glm
)
