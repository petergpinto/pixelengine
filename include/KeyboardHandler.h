#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Action.h"

class KeyboardHandler {
public:
	const static int numKeys = 1024;

private:
	std::vector<Action> keyActions[numKeys];
	std::shared_ptr<GLFWwindow> callbackWindow;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	static bool keysPressed[numKeys];
	KeyboardHandler();
	void setCallback(std::shared_ptr<GLFWwindow>);
	void handleInput(double);
	void registerAction(int, Action);
};