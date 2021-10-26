// PixelEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum ERROR {
	NONE = 0,
	GLFW_INIT = 1,
	GLFW_WINDOW_CREATE = 2,
};

class PixelEngine {
private:
	GLFWwindow* currentWindow;
	ERROR error;

public:
	PixelEngine();
	ERROR checkError();
	void terminate();
	GLFWwindow* getWindow();
	static int initializeEngine();
	static GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor*);
	static int shouldTerminate(GLFWwindow*);
};

// TODO: Reference additional headers your program requires here.
