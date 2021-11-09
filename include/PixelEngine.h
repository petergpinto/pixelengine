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
#include "transform.h"
#include "CellRenderer.h"
#include "Cell.h"
#include "Action.h"


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
	std::shared_ptr<Transform> worldOrigin;
	KeyboardHandler* keyboardHandler;
	MouseHandler* mouseHandler;
	bool needRunDeletion = false;

	//FPS counter vars
	double fps, fpsTotalTime = 0.0f;
	int fpsFrameCount = 0;

public:
	//Primary owner of all GameObjects, used to render and tick all objects each frame
	//When a GameObject is removed from here, the object may still exist but will not render \
	// or tick and be destroyed when the last reference to the object goes out-of-scope
	std::vector<std::shared_ptr<GameObject>> gameObjects;  

	PixelEngine(bool vsync = true, int monitor = 0);
	~PixelEngine();
	ERROR checkError();	//Return any openGL or GLFW error
	void terminate(); //Shutdown the engine
	GLFWwindow* getWindow(); //Return a pointer to the current window
	float getWidth(); //Of current window
	float getHeight(); //Of current window
	void fpsCounter(double, int, bool debugPrint = false); //Call once per frame to count FPS, will print to console if debugPrint is true
	void swapBufferOrFlush(); //Call glfwSwapBuffers if VSync is enabled, otherwise glFlush
	std::shared_ptr<Transform> getWorldOrigin();  //Return a pointer to the origin of the world, useful as an anchor point
	void addTransformToOrigin(Transform); //Move the origin around
	void renderObjects(); //Call Render on all GameObjects
	void tickObjects(double); //Call tick on all GameObjects
	void deleteMarkedObjects(); //Delete GameObjects objects marked for deletion (maybe no longer necessary with shared_ptr)
	void setGLFWContext(); //Set glfw context to current window
	void setKeyboardAndMouseCallbacks(); //instantiate input callbacks
	void initializeOpenGLViewport(); //setup openGL viewport
	void registerMouseAction(int, std::function<void(double)>);  //Add an action object to call a function against a GameObject when a mouse button is pressed
	void registerKeyboardAction(int, Action); //Same as registerMouseAction but for keyboard presses
	void handleKeyboardAndMouseInput(double);  //Do the function calls setup by registerKeyboardAction and registerMouseAction
	Position getMousePosition(); //Process and return mouse data
	Position getMouseMovement(); // --

	static int initializeEngine(); //run GLFW initialization, not dependent on the engine object
	static GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor*, bool vsync = true);  //Initialize a borderless fullscreen window on the referenced monitor
	static int shouldTerminate(GLFWwindow*); //Test if the GLFWwindow should terminate according to the GLFW library
};

// TODO: Reference additional headers your program requires here.
