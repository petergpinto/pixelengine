﻿// PixelEngine.cpp : Defines the entry point for the application.
//

#include "PixelEngine.h"
namespace PixelEngine {

	int initializeEngine() {
		return glfwInit();
	}

	GLFWwindow* createBorderlessFullscreenWindow(GLFWmonitor* monitor) {
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", glfwGetPrimaryMonitor(), NULL);
		return window;
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