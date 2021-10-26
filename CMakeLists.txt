# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("PixelEngine")
include_directories("include")
include_directories("lib/glad/include")

file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

# Include sub-projects.
add_subdirectory("lib/glfw-3.3.4")
add_subdirectory("lib/glad")
add_subdirectory ("src")





