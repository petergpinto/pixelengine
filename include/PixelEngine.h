// PixelEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


enum ERROR {
	NONE = 0,
	GLFW_INIT = 1,
	GLFW_WINDOW_CREATE = 2,
};

class PixelEngine {
private:
	GLFWwindow* currentWindow;
	ERROR error;
	float currentWindowHeight;
	float currentWindowWidth;

public:
	PixelEngine();
	ERROR checkError();
	void terminate();
	GLFWwindow* getWindow();
	float getWidth();
	float getHeight();
	static int initializeEngine();
	static GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor*);
	static int shouldTerminate(GLFWwindow*);
};

// TODO: Reference additional headers your program requires here.
