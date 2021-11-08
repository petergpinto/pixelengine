#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>
#include "GameObject.h"
#include "Action.h"

class KeyboardHandler {
public:
	const static int numKeys = 1024;

private:
	std::vector<Action> keyActions[numKeys];

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	static bool keysPressed[numKeys];
	KeyboardHandler();
	void setCallback(GLFWwindow*);
	void handleInput(double);
	void registerAction(int, Action);
};