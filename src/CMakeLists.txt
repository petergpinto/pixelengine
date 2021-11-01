# CMakeList.txt : CMake project for PixelEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
if(MSVC)
	add_executable (PixelEngine "main.cpp") # Add WIN32 for release
else()
	add_executable (PixelEngine "main.cpp")
endif()

target_link_libraries(PixelEngine glad)

target_sources(PixelEngine PRIVATE "PixelEngine.cpp")
target_sources(PixelEngine PRIVATE "shader/shader.cpp")
target_sources(PixelEngine PRIVATE "texture/texture.cpp")
target_sources(PixelEngine PRIVATE "ResourceManager.cpp")
target_sources(PixelEngine PRIVATE "texture/SpriteRenderer.cpp")
target_sources(PixelEngine PRIVATE "input/KeyboardHandler.cpp")
target_sources(PixelEngine PRIVATE "input/MouseHandler.cpp")
target_sources(PixelEngine PRIVATE "GameObject.cpp")
target_sources(PixelEngine PRIVATE "Player.cpp")

#Debug
target_sources(PixelEngine PRIVATE "RenderTest.cpp")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


target_link_libraries(PixelEngine glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(PixelEngine OpenGL::GL)

target_compile_features(PixelEngine PRIVATE cxx_std_17)

# TODO: Add tests and install targets if needed.
