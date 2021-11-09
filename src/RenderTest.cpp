//File to test rendering functions
//Should be excluded from final builds

#include "RenderTest.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GameObject.h"
#include "Player.h"
#include "CellRenderer.h"
#include "Cell.h"
#include <algorithm>
#include <memory>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float xPos, yPos, deltaTime, rotation;
PixelEngine* engine;
SpriteRenderer  *renderer;
CellRenderer* cellrenderer;
void shutdown(double);
void createSpriteOnCursor(double);
void dragWorld(double);

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

	engine->registerMouseAction(GLFW_MOUSE_BUTTON_LEFT, std::bind(&createSpriteOnCursor, std::placeholders::_1));

	engine->initializeOpenGLViewport();

	ResourceManager::LoadShader("../resources/shaders/sprite.vs", "../resources/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("../resources/shaders/cell.vs", "../resources/shaders/cell.frag", nullptr, "cell");

	glm::mat4 projection = glm::ortho<float>(0.0f, static_cast<float>(engine->getWidth()), static_cast<float>(engine->getHeight()), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	Shader sprite = ResourceManager::GetShader("sprite");
	Shader cell = ResourceManager::GetShader("cell");
	renderer = new SpriteRenderer(sprite);
	cellrenderer = new CellRenderer(cell);
	cellrenderer->SetProjectionMatrix(projection);

	ResourceManager::LoadTexture("../resources/textures/awesomeface2.png", true, "face");
	ResourceManager::LoadTexture("../resources/textures/awesomeface.png", true, "faceHighRes");
	ResourceManager::LoadTexture("../resources/textures/test.png", true, "test");


	deltaTime = 0.0f;
	float lastFrame = 0.0f;
	xPos = static_cast<float>(engine->getWidth() / 2);
	yPos = static_cast<float>(engine->getHeight() / 2);
	rotation = 0.0f;

	engine->gameObjects.push_back(std::make_shared<GameObject> (GameObject(renderer, ResourceManager::GetTexture("faceHighRes"), engine->getWorldOrigin())));
	engine->gameObjects.push_back(std::make_shared<GameObject>(GameObject(renderer, ResourceManager::GetTexture("faceHighRes"),
		engine->getWorldOrigin(),
		Transform(Position(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)),  Size(100.0f, 100.0f), Rotation())
	)));
	engine->gameObjects.push_back(std::make_shared<GameObject>(
		GameObject(renderer, ResourceManager::GetTexture("test"),
			engine->getWorldOrigin(), 
			Transform(Position(), Size(500.0f,500.0f), Rotation())
		))
	);
	Player player = Player(renderer, ResourceManager::GetTexture("face"), engine->getWorldOrigin());
	std::shared_ptr<Player> p = std::make_shared<Player>(player);
	//Binds the function Player::moveLeft running on the object instance "player" to the A key, following functions do similar
	engine->registerKeyboardAction(GLFW_KEY_A, Action(p, std::bind(&Player::moveLeft, p.get(), std::placeholders::_1)));
	engine->registerKeyboardAction(GLFW_KEY_D, Action(p, std::bind(&Player::moveRight, p.get(), std::placeholders::_1)));
	engine->registerKeyboardAction(GLFW_KEY_W, Action(p, std::bind(&Player::moveUp, p.get(), std::placeholders::_1)));
	engine->registerKeyboardAction(GLFW_KEY_S, Action(p, std::bind(&Player::moveDown, p.get(), std::placeholders::_1)));
	engine->registerKeyboardAction(GLFW_KEY_U, Action(p, std::bind(&Player::destroy, p.get(), std::placeholders::_1)));

	engine->gameObjects.push_back(std::move(p));

	std::shared_ptr<GameObject> g = std::make_shared<GameObject>(GameObject(renderer, ResourceManager::GetTexture("faceHighRes"), engine->getWorldOrigin()));
	engine->registerKeyboardAction(GLFW_KEY_ESCAPE, Action(g, std::bind(&shutdown, std::placeholders::_1)));


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
		engine->renderObjects();
		engine->tickObjects(deltaTime);
		//Delete objects marked for deletion
		engine->deleteMarkedObjects();

		//rend->DrawCell(glm::vec2(500.0f, 500.0f), glm::vec2(1, 1));

		/* Swap front and back buffers */
		engine->swapBufferOrFlush();

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void createSpriteOnCursor(double deltaTime) {
	engine->gameObjects.push_back(std::make_unique<Cell>(Cell(cellrenderer, engine->getWorldOrigin(), engine->getMousePosition())));
	//engine->gameObjects.push_back(std::make_unique<GameObject>(GameObject(ResourceManager::GetTexture("face"), engine->getWorldOrigin(), Transform(engine->getMousePosition(), Size(100.0f, 100.0f)))));
}

void dragWorld(double deltaTime) {
	double magnitude = 100.0f;
	engine->addTransformToOrigin(Transform(Position(engine->getMouseMovement().x * deltaTime * magnitude, engine->getMouseMovement().y * deltaTime * magnitude)));
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