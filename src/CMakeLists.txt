# CMakeList.txt : CMake project for PixelEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
if(MSVC)
	add_executable (PixelEngine WIN32 "main.cpp" "main.h")
else()
	add_executable (PixelEngine "main.cpp" "main.h")
endif()

target_link_libraries(PixelEngine glad)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


target_link_libraries(PixelEngine glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(PixelEngine OpenGL::GL)


# TODO: Add tests and install targets if needed.
