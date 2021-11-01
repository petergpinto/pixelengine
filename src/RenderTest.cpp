//File to test rendering functions
//Should be excluded from final builds

#include "RenderTest.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GameObject.h"
#include "Player.h"
#include <algorithm>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float xPos, yPos, deltaTime, rotation;
PixelEngine* engine;
SpriteRenderer  *Renderer;
void shutdown(double);
void createSpriteOnCursor(double);

int keyPressed = 0;

int RenderTest() {
	/* Initialize the library */
	engine = new PixelEngine(false);

	if (engine->checkError() != ERROR::NONE) {
		engine->terminate();
		return engine->checkError();
	}

	/* Make the window's context current */
	engine->setGLFWContext();

	engine->setKeyboardAndMouseCallbacks();

	engine->registerKeyboardAction(GLFW_KEY_ESCAPE, std::bind(&shutdown, std::placeholders::_1));
	engine->registerMouseAction(GLFW_MOUSE_BUTTON_LEFT, std::bind(&createSpriteOnCursor, std::placeholders::_1));

	engine->initializeOpenGLViewport();

	ResourceManager::LoadShader("../resources/shaders/sprite.vs", "../resources/shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho<float>(0.0f, static_cast<float>(engine->getWidth()), static_cast<float>(engine->getHeight()), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	Shader sprite = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(sprite);

	ResourceManager::LoadTexture("../resources/textures/awesomeface2.png", true, "face");
	ResourceManager::LoadTexture("../resources/textures/awesomeface.png", true, "faceHighRes");
	ResourceManager::LoadTexture("../resources/textures/test.png", true, "test");


	deltaTime = 0.0f;
	float lastFrame = 0.0f;
	xPos = static_cast<float>(engine->getWidth() / 2);
	yPos = static_cast<float>(engine->getHeight() / 2);
	rotation = 0.0f;

	engine->gameObjects.push_back(std::make_unique<GameObject> (GameObject(ResourceManager::GetTexture("faceHighRes"))));
	engine->gameObjects.push_back(std::make_unique<GameObject>(GameObject(ResourceManager::GetTexture("faceHighRes"),
		Position(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)), 
		Position(), 
		Size(100.0f, 100.0f))));
	engine->gameObjects.push_back(std::make_unique<GameObject>(GameObject(ResourceManager::GetTexture("test"), Position(), Position(), Size(500.0f,500.0f))));
	Player player = Player(ResourceManager::GetTexture("face"));
	std::unique_ptr<Player> p = std::make_unique<Player>(player);
	//Binds the function Player::moveLeft running on the object instance "player" to the A key, following functions do similar
	engine->registerKeyboardAction(GLFW_KEY_A, std::bind(&Player::moveLeft, p.get(), std::placeholders::_1));
	engine->registerKeyboardAction(GLFW_KEY_D, std::bind(&Player::moveRight, p.get(), std::placeholders::_1));
	engine->registerKeyboardAction(GLFW_KEY_W, std::bind(&Player::moveUp, p.get(), std::placeholders::_1));
	engine->registerKeyboardAction(GLFW_KEY_S, std::bind(&Player::moveDown, p.get(), std::placeholders::_1));
	engine->registerKeyboardAction(GLFW_KEY_U, std::bind(&Player::destroy, p.get(), std::placeholders::_1));

	engine->gameObjects.push_back(std::move(p));

	/* Loop until the user closes the window */
	while (!PixelEngine::shouldTerminate(engine->getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//std::cout << deltaTime << std::endl;
		engine->fpsCounter(deltaTime, 100);
		engine->handleKeyboardAndMouseInput(deltaTime);

		//Call Render() on each GameObject, except if it is marked for deletion
		engine->renderObjects(Renderer);
		//Delete objects marked for deletion
		engine->deleteMarkedObjects();

		/* Swap front and back buffers */
		engine->swapBufferOrFlush();

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void createSpriteOnCursor(double deltaTime) {
	Texture2D face = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(face,
		glm::vec2(MouseHandler::xpos, MouseHandler::ypos), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	std::cout << MouseHandler::xpos << " " << MouseHandler::ypos << std::endl;
}

void shutdown(double deltaTime) {
	delete engine;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keyPressed = key; // Breakout.Keys[key] = true;
		else if (action == GLFW_RELEASE)
			keyPressed = 0; // Breakout.Keys[key] = false;
	}
}