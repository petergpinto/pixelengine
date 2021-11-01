// PixelEngine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <algorithm>
#include <functional>
#include <memory>

#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "transform.h"
#include "GameObject.h"
#include "MouseHandler.h"
#include "KeyboardHandler.h"


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
	bool vsyncEnabled;
	Transform worldOrigin;
	KeyboardHandler* keyboardHandler;
	MouseHandler* mouseHandler;

	//FPS counter vars
	double fps, fpsTotalTime = 0.0f;
	int fpsFrameCount = 0;

public:
	std::vector<std::unique_ptr<GameObject>> gameObjects;

	PixelEngine(bool vsync = true, int monitor = 0);
	~PixelEngine();
	ERROR checkError();
	void terminate();
	GLFWwindow* getWindow();
	float getWidth();
	float getHeight();
	void fpsCounter(double, int, bool debugPrint = false);
	void swapBufferOrFlush();
	Transform getWorldOrigin();
	void renderObjects(SpriteRenderer*);
	void deleteMarkedObjects();
	void setGLFWContext();
	void setKeyboardAndMouseCallbacks();
	void initializeOpenGLViewport();
	void registerMouseAction(int, std::function<void(double)>);
	void registerKeyboardAction(int, std::function<void(double)>);
	void handleKeyboardAndMouseInput(double);

	static int initializeEngine();
	static GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor*, bool vsync = true);
	static int shouldTerminate(GLFWwindow*);
};

// TODO: Reference additional headers your program requires here.
