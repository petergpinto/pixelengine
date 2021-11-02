// PixelEngine.cpp : Defines the entry point for the application.
//

#include "PixelEngine.h"

PixelEngine::PixelEngine(bool vsync, int monitor) {
	error = ERROR::NONE;
	vsyncEnabled = vsync;
	this->worldOrigin = Transform();
	if (!PixelEngine::initializeEngine())
		error = ERROR::GLFW_INIT;
	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	currentWindow = PixelEngine::createBorderlessFullscreenWindow(monitors[monitor], vsync);
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	currentWindowHeight = mode->height;
	currentWindowWidth = mode->width;
	if (!currentWindow)
		error = ERROR::GLFW_WINDOW_CREATE;
	mouseHandler = new MouseHandler();
	keyboardHandler = new KeyboardHandler();
}

PixelEngine::~PixelEngine() {
	this->shouldTerminate(currentWindow);
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

Transform PixelEngine::getWorldOrigin() {
	return this->worldOrigin;
}

void PixelEngine::renderObjects(SpriteRenderer* renderer) {
	for (auto& g : this->gameObjects) {
		if (!g->shouldDelete())
			g->Render(renderer);
		else
			needRunDeletion = true; //check if there are objects that need deletion here and only run deleteMarkedObjects if there is at least 1
									//At the same time, we can remove stale registered actions
	}
}

void PixelEngine::deleteMarkedObjects() {
	if (needRunDeletion) {
		this->gameObjects.erase(std::remove_if(this->gameObjects.begin(), this->gameObjects.end(), [&](std::unique_ptr<GameObject> & obj) {
			return obj->shouldDelete();
		}), this->gameObjects.end());
		needRunDeletion = false;
		return;
	}
	else {
		return;
	}
}

void PixelEngine::setGLFWContext() {
	glfwMakeContextCurrent(currentWindow);
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf
}

void PixelEngine::setKeyboardAndMouseCallbacks() {
	keyboardHandler->setCallback(currentWindow);
	mouseHandler->setMouseButtonCallback(currentWindow);
	mouseHandler->setPositionCallback(currentWindow);
}

void PixelEngine::initializeOpenGLViewport() {
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void PixelEngine::registerMouseAction(int button, std::function<void(double)> action) {
	mouseHandler->registerAction(button, action);
}

void PixelEngine::registerKeyboardAction(int key, std::function<void(double)> action) {
	keyboardHandler->registerAction(key, action);
}

void PixelEngine::handleKeyboardAndMouseInput(double deltaTime) {
	mouseHandler->handleInput(deltaTime);
	keyboardHandler->handleInput(deltaTime);
}