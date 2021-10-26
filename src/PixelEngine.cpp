// PixelEngine.cpp : Defines the entry point for the application.
//

#include "PixelEngine.h"

PixelEngine::PixelEngine() {
	error = ERROR::NONE;
	if (!PixelEngine::initializeEngine())
		error = ERROR::GLFW_INIT;
	currentWindow = PixelEngine::createBorderlessFullscreenWindow(glfwGetPrimaryMonitor());
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	currentWindowHeight = mode->height;
	currentWindowWidth = mode->width;
	if (!currentWindow)
		error = ERROR::GLFW_WINDOW_CREATE;
}

ERROR PixelEngine::checkError() {
	return error;
}

void PixelEngine::terminate() {
	glfwTerminate();
}

GLFWwindow* PixelEngine::getWindow() {
	return currentWindow;
}

int PixelEngine::initializeEngine() {
	return glfwInit();
}

GLFWwindow* PixelEngine::createBorderlessFullscreenWindow(GLFWmonitor* monitor) {
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", glfwGetPrimaryMonitor(), NULL);
	return window;
}

int PixelEngine::shouldTerminate(GLFWwindow* window) {
	return glfwWindowShouldClose(window);
}

float PixelEngine::getHeight() {
	return currentWindowHeight;
}

float PixelEngine::getWidth() {
	return currentWindowWidth;
}

/*
int main(void)
{
	/* Initialize the library 
	if (!glfwInit())
		return -1;
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", glfwGetPrimaryMonitor(), NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current 
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf

	/* Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
//		glClearColor(1.0, 1.0, 1.0, 1.0);
	//	glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers 
		glfwSwapBuffers(window);

		/* Poll for and process events 
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int WinMain(void) {
	main();
}
*/