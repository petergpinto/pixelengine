// PixelEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace PixelEngine {

	int initializeEngine();
	GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor*);
}


// TODO: Reference additional headers your program requires here.
