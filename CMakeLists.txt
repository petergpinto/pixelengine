# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("PixelEngine")
include_directories("include")

# Include sub-projects.
add_subdirectory("glfw-3.3.4")
add_subdirectory("glad")
add_subdirectory ("src")





