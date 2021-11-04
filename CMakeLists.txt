# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

ADD_CUSTOM_TARGET(copy_resources)
ADD_CUSTOM_COMMAND(
        TARGET copy_resources POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_CURRENT_SOURCE_DIR}/resources
				${CMAKE_CURRENT_BINARY_DIR}/resources
        COMMENT "Copying Files for target: PixelEngine" VERBATIM 
        )

project ("PixelEngine")
include_directories("include")
include_directories("lib/glad/include")

#file(COPY resources DESTINATION "${CMAKE_BINARY_DIR}")

# Include sub-projects.
add_subdirectory("lib/glfw-3.3.4")
add_subdirectory("lib/glad")
add_subdirectory ("src")





