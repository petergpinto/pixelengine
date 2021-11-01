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
std::vector<std::unique_ptr<GameObject>> gameObjects = {};
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
	glfwMakeContextCurrent(engine->getWindow());
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf

	KeyboardHandler* keyboardHandler = new KeyboardHandler();
	keyboardHandler->setCallback(engine->getWindow());
	keyboardHandler->registerAction(GLFW_KEY_ESCAPE, shutdown);

	MouseHandler* mouseHandler = new MouseHandler();
	mouseHandler->setMouseButtonCallback(engine->getWindow());
	mouseHandler->setPositionCallback(engine->getWindow());
	mouseHandler->registerAction(GLFW_MOUSE_BUTTON_LEFT, createSpriteOnCursor);

	glViewport(0, 0, engine->getWidth(), engine->getHeight());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


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

	gameObjects.push_back(std::make_unique<GameObject> (GameObject(ResourceManager::GetTexture("faceHighRes"))));
	gameObjects.push_back(std::make_unique<GameObject>(GameObject(ResourceManager::GetTexture("faceHighRes"),
		Position(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)), 
		Position(), 
		Size(100.0f, 100.0f))));
	gameObjects.push_back(std::make_unique<GameObject>(GameObject(ResourceManager::GetTexture("test"), Position(), Position(), Size(500.0f,500.0f))));
	Player player = Player(ResourceManager::GetTexture("face"));
	std::unique_ptr<Player> p = std::make_unique<Player>(player);
	//Binds the function Player::moveLeft running on the object instance "player" to the A key, following functions do similar
	keyboardHandler->registerAction(GLFW_KEY_A, std::bind(&Player::moveLeft, p.get(), std::placeholders::_1));
	keyboardHandler->registerAction(GLFW_KEY_D, std::bind(&Player::moveRight, p.get(), std::placeholders::_1));
	keyboardHandler->registerAction(GLFW_KEY_W, std::bind(&Player::moveUp, p.get(), std::placeholders::_1));
	keyboardHandler->registerAction(GLFW_KEY_S, std::bind(&Player::moveDown, p.get(), std::placeholders::_1));
	keyboardHandler->registerAction(GLFW_KEY_U, std::bind(&Player::destroy, p.get(), std::placeholders::_1));

	gameObjects.push_back(std::move(p));

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
		keyboardHandler->handleInput(deltaTime);
		mouseHandler->handleInput(deltaTime);

		for (auto& g : gameObjects) {
			if (!g->shouldDelete())
				g->Render(Renderer);
		}

		//Delete objects marked for deletion
		gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [&](std::unique_ptr<GameObject> & obj) {
			return obj->shouldDelete();
		}), gameObjects.end());		

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