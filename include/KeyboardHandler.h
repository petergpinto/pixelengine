#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

class KeyboardHandler {
public:
	const static int numKeys = 1024;

private:
	std::vector<std::function<void(void)>> keyActions[numKeys];

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

public:
	static bool keysPressed[numKeys];
	KeyboardHandler();
	void setCallback(GLFWwindow*);
	void handleInput();
	void registerAction(int, std::function<void(void)>);
};