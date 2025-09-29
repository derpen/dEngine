cmake_minimum_required(VERSION 3.16)
project(dEngine)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendor/SDL
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

file(GLOB_RECURSE src_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
src/*
)

add_executable(dEngine WIN32 ${src_files})

# add_executable(dEngine WIN32 src/hello.c)

# Link to the actual SDL3 library.
target_link_libraries(dEngine PRIVATE SDL3::SDL3)
