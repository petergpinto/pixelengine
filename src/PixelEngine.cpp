// PixelEngine.cpp : Defines the entry point for the application.
//

#include "PixelEngine.h"

PixelEngine::PixelEngine(bool vsync) {
	error = ERROR::NONE;
	vsyncEnabled = vsync;
	if (!PixelEngine::initializeEngine())
		error = ERROR::GLFW_INIT;
	currentWindow = PixelEngine::createBorderlessFullscreenWindow(glfwGetPrimaryMonitor(), vsync);
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

void PixelEngine::swapBufferOrFlush() {
	if(vsyncEnabled)
		glfwSwapBuffers(this->getWindow());
	else 
		glFlush();
}

GLFWwindow* PixelEngine::createBorderlessFullscreenWindow(GLFWmonitor* monitor, bool vsync) {
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	if(!vsync)
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE); //Disable Vsync

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

void PixelEngine::fpsCounter(double deltaTime, int n, bool debugPrint) {
	//Count the average fps over n frames
	fpsTotalTime += deltaTime;
	if (fpsFrameCount >= n) {
		fps = n / fpsTotalTime;
		fpsFrameCount = 0;
		fpsTotalTime = 0.0f;
		if(debugPrint)
			std::cout << fps << std::endl;
	}
	else {
		fpsFrameCount++;
	}
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