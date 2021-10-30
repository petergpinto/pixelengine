#include "KeyboardHandler.h"

bool KeyboardHandler::keysPressed[] = { 0 };

KeyboardHandler::KeyboardHandler() {
	for (int i = 0; i < KeyboardHandler::numKeys; i++) {
		keyActions[i] = {};
	}
}

void KeyboardHandler::setCallback(GLFWwindow* window) {
	glfwSetKeyCallback(window, key_callback);
}

void KeyboardHandler::handleInput(double deltaTime) {
	for (int i = 0; i < KeyboardHandler::numKeys; i++) {
		if (KeyboardHandler::keysPressed[i]) {
			//run key actions
			for (std::function<void(double)> f : keyActions[i]) {
				f(deltaTime);
			}
		}
	}
}

void KeyboardHandler::registerAction(int key, std::function<void(double)> func) {
	keyActions[key].push_back(func);  //std::vector<std::function<void(void)>>
}


void KeyboardHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			KeyboardHandler::keysPressed[key] = true;
		else if (action == GLFW_RELEASE)
			KeyboardHandler::keysPressed[key] = false;
	}
}