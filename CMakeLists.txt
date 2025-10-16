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

include_directories(include)

find_package(Vulkan REQUIRED)

# External libraries
add_subdirectory(vendor/vk-bootstrap)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/fastgltf)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imgui)

# stb
include_directories(vendor/stb_image)

# Vulkan Memory Allocator
include_directories(vendor/VulkanMemoryAllocator/include)

###############################
### Shaders shenanigans
###############################
#target_compile_definitions(${PROJECT_NAME} PRIVATE VK_USE_PLATFORM_WIN32_KHR) ## Not needed?

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/assets/shaders/*.comp"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/assets/shaders/${FILE_NAME}.spv")
  message(STATUS "Compiling " ${GLSL})
  #message(STATUS COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL} "-o" ${SPIRV})
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${GLSL} "-o" ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )

## Add shader files to IDE
source_group("Shaders" FILES ${GLSL_SOURCE_FILES})
set_source_files_properties(${GLSL_SOURCE_FILES} PROPERTIES LANGUAGE GLSL)
set(PROJECT_FILES ${src_files} ${GLSL_SOURCE_FILES})
add_executable(dEngine WIN32 ${PROJECT_FILES})

add_dependencies(${PROJECT_NAME} Shaders)

## Copy assets files to .exe directory
## Might need a rework soon, might be worth to copy the .exe file into the asset folder
## or use symlink. The point is to not make copy of asset folder
set (destination "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>/assets")
add_custom_command(
     TARGET ${PROJECT_NAME} POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${destination}"
     DEPENDS ${destination}
)
###############################
### Shaders shenanigans end
###############################


target_link_libraries(dEngine PRIVATE 
imgui::imgui
SDL3::SDL3
vk-bootstrap::vk-bootstrap
fmt::fmt
Vulkan::Vulkan
fastgltf::fastgltf
glm::glm
)
