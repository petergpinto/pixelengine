#include "MouseHandler.h"

bool MouseHandler::mouseButtonsPressed[] = { 0 };
double MouseHandler::xpos = 0;
double MouseHandler::ypos = 0;

MouseHandler::MouseHandler() {
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++) {
		mouseActions[i] = {};
	}
}

void MouseHandler::setPositionCallback(GLFWwindow* window) {
	glfwSetCursorPosCallback(window, MouseHandler::cursor_position_callback);
}

void MouseHandler::setMouseButtonCallback(GLFWwindow* window) {
	glfwSetMouseButtonCallback(window, MouseHandler::mouse_button_callback);
}

void MouseHandler::handleInput(double deltaTime) {
	for (int i = 0; i < NUM_MOUSE_BUTTONS; i++) {
		if (MouseHandler::mouseButtonsPressed[i]) {
			//run key actions
			for (std::function<void(double)> f : mouseActions[i]) {
				f(deltaTime);
			}
		}
	}
	previousXpos = MouseHandler::xpos;
	previousYpos = MouseHandler::ypos;
}

void MouseHandler::registerAction(int button, std::function<void(double)> action) {
	mouseActions[button].push_back(action);
}

void MouseHandler::pollMouseEvents() {

}

void MouseHandler::setCursorMode(int) {

}

void MouseHandler::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler::xpos = xpos;
	MouseHandler::ypos = ypos;
}

void MouseHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (button >= 0 && button < NUM_MOUSE_BUTTONS)
	{
		if (action == GLFW_PRESS)
			MouseHandler::mouseButtonsPressed[button] = true;
		else if (action == GLFW_RELEASE)
			MouseHandler::mouseButtonsPressed[button] = false;
	}
}

Position MouseHandler::getDeltaMouseMovement() {
	return Position(MouseHandler::xpos - this->previousXpos, MouseHandler::ypos - this->previousYpos);
}