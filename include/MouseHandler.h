#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "transform.h"

#define NUM_MOUSE_BUTTONS 8 

class MouseHandler {

private:
	std::vector<std::function<void(double)>> mouseActions[NUM_MOUSE_BUTTONS];
	std::shared_ptr<GLFWwindow> callbackWindowCursor;
	std::shared_ptr<GLFWwindow> callbackWindowButton;

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

public:
	static double xpos, ypos;
	double previousXpos = 0, previousYpos = 0;
	static bool mouseButtonsPressed[NUM_MOUSE_BUTTONS];
	MouseHandler();
	void setPositionCallback(std::shared_ptr<GLFWwindow>);
	void setMouseButtonCallback(std::shared_ptr<GLFWwindow>);
	void handleInput(double);
	void registerAction(int, std::function<void(double)>);
	void pollMouseEvents();
	void setCursorMode(int);
	Position getDeltaMouseMovement();
};