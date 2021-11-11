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
target_sources(PixelEngine PRIVATE "texture/CellRenderer.cpp")
target_sources(PixelEngine PRIVATE "Cell.cpp")
target_sources(PixelEngine PRIVATE "input/Action.cpp")

target_sources(PixelEngine PRIVATE "imgui/imgui.cpp")
target_sources(PixelEngine PRIVATE "imgui/imgui_demo.cpp")
target_sources(PixelEngine PRIVATE "imgui/imgui_draw.cpp")
target_sources(PixelEngine PRIVATE "imgui/imgui_tables.cpp")
target_sources(PixelEngine PRIVATE "imgui/imgui_widgets.cpp")

target_sources(PixelEngine PRIVATE "imgui/backends/imgui_impl_glfw.cpp")
target_sources(PixelEngine PRIVATE "imgui/backends/imgui_impl_opengl3.cpp")

#Debug
target_sources(PixelEngine PRIVATE "RenderTest.cpp")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


target_link_libraries(PixelEngine glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(PixelEngine OpenGL::GL)

add_dependencies(PixelEngine copy_resources)

# TODO: Add tests and install targets if needed.
