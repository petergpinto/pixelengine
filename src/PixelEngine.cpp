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


//--------------GLFW Functions--------------//
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

void PixelEngine::swapBufferOrFlush() {
	if (vsyncEnabled)
		glfwSwapBuffers(this->getWindow());
	else
		glFlush();
}

int PixelEngine::initializeEngine() {
	return glfwInit();
}

void PixelEngine::terminate() {
	glfwTerminate();
}

int PixelEngine::shouldTerminate(GLFWwindow* window) {
	return glfwWindowShouldClose(window);
}

void PixelEngine::setGLFWContext() {
	glfwMakeContextCurrent(currentWindow);
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf
}
//-------------END GLFW FUNCTIONS-----------------//


//----------------OPENGL FUNCTIONS------------------//
void PixelEngine::initializeOpenGLViewport() {
	glViewport(0, 0, this->getWidth(), this->getHeight());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
//----------------END OPENGL FUNCTIONS--------------//


//--------------WINDOW FUNCTIONS------------------//
float PixelEngine::getHeight() {
	return currentWindowHeight;
}

float PixelEngine::getWidth() {
	return currentWindowWidth;
}

GLFWwindow* PixelEngine::getWindow() {
	return currentWindow;
}
//----------------END WINDOW FUNCTIONS----------------//


//----------------RENDERING FUNCTIONS------------------//
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

void PixelEngine::renderObjects() {
	for (auto& g : this->gameObjects) {
		if (!g->shouldDelete()) {
			g->Render();
		}
		else
			needRunDeletion = true; //check if there are objects that need deletion here and only run deleteMarkedObjects if there is at least 1
									//At the same time, we can remove stale registered actions
	}
}
//---------------END RENDERING FUNCTIONS--------------//




//---------------GameObject MANAGEMENT FUNCTIONS------------///
void PixelEngine::deleteMarkedObjects() {
	if (needRunDeletion) {
		this->gameObjects.erase(std::remove_if(this->gameObjects.begin(), this->gameObjects.end(), [&](std::shared_ptr<GameObject> & obj) {
			return obj->shouldDelete();
		}), this->gameObjects.end());
		needRunDeletion = false;
		return;
	}
	else {
		return;
	}
}

void PixelEngine::tickObjects(double deltaTime) {
	for (auto& g : this->gameObjects) {
		if (!g->shouldDelete()) {
			g->tick(deltaTime);
		}
		else
			needRunDeletion = true; //check if there are objects that need deletion here and only run deleteMarkedObjects if there is at least 1
									//At the same time, we can remove stale registered actions
	}
}
//-------------END GameObject MANAGEMENT FUNCTIONS-------------//


//-------------USER INPUT FUNCTIONS---------------//
void PixelEngine::setKeyboardAndMouseCallbacks() {
	keyboardHandler->setCallback(currentWindow);
	mouseHandler->setMouseButtonCallback(currentWindow);
	mouseHandler->setPositionCallback(currentWindow);
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
//----------------END USER INPUT FUNCTIONS----------------//


//----------------TRANSFORM FUNCTIONS------------------//
Position PixelEngine::getMousePosition() {
	return Position(mouseHandler->xpos, mouseHandler->ypos);
}

void PixelEngine::addTransformToOrigin(Transform offset) { 
	this->worldOrigin += offset;
}

Position PixelEngine::getMouseMovement() {
	return mouseHandler->getDeltaMouseMovement();
}

Transform* PixelEngine::getWorldOrigin() {
	return &(this->worldOrigin);
}
//---------------END TRANSFORM FUNCTIONS------------------//