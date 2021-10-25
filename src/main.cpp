// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "PixelEngine.h"

int main(void)
{
	/* Initialize the library */
	if (!PixelEngine::initializeEngine())
		return -1;
	GLFWwindow* window = PixelEngine::createBorderlessFullscreenWindow(glfwGetPrimaryMonitor());

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int WinMain(void) {
	main();
}
