//File to test rendering functions
//Should be excluded from final builds

#include "RenderTest.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "GameObject.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float xPos, yPos, deltaTime, rotation;
PixelEngine* engine;
SpriteRenderer  *Renderer;
std::vector<GameObject*> gameObjects = {};
GameObject* Player;
void runW(double);
void runA(double);
void runS(double);
void runD(double);
void runQ(double);
void runE(double);
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
	keyboardHandler->registerAction(GLFW_KEY_W, runW);
	keyboardHandler->registerAction(GLFW_KEY_A, runA);
	keyboardHandler->registerAction(GLFW_KEY_S, runS);
	keyboardHandler->registerAction(GLFW_KEY_D, runD);
	keyboardHandler->registerAction(GLFW_KEY_Q, runQ);
	keyboardHandler->registerAction(GLFW_KEY_E, runE);
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

	gameObjects.push_back(new GameObject(ResourceManager::GetTexture("faceHighRes"), Renderer));
	gameObjects.push_back(new GameObject(ResourceManager::GetTexture("faceHighRes"), Renderer,
		Position(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)), 
		Position(), 
		Size(100.0f, 100.0f)));
	gameObjects.push_back(new GameObject(ResourceManager::GetTexture("test"), Renderer, Position(), Position(), Size(500.0f,500.0f)));
	Player = new GameObject(ResourceManager::GetTexture("face"), Renderer, Position(), Position(xPos, yPos));
	gameObjects.push_back(Player);

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

		for (GameObject* g : gameObjects) {
			g->Render();
		}

		//Texture2D faceHighRes = ResourceManager::GetTexture("faceHighRes");
		//Renderer->DrawSprite(faceHighRes,
			//glm::vec2(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)), glm::vec2(500.0f, 500.0f), -15.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		//Texture2D test = ResourceManager::GetTexture("test");
		//Renderer->DrawSprite(test,
		//	glm::vec2(0.0f, 0.0f), glm::vec2(500.0f, 500.0f), 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		//Texture2D face = ResourceManager::GetTexture("face");
		//Renderer->DrawSprite(face,
		//	glm::vec2(xPos, yPos), glm::vec2(500.0f, 500.0f), rotation, glm::vec3(1.0f, 1.0f, 1.0f));

		//static_cast<float>(engine->getWidth() /2), static_cast<float>(engine->getHeight() / 2)
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

void runW(double deltaTime) {
	Player->addLocalPositionOffset(Position(0.0f, -100 * deltaTime));
}
void runS(double deltaTime) {
	Player->addLocalPositionOffset(Position(0.0f, 100 * deltaTime));
}
void runA(double deltaTime) {
	Player->addLocalPositionOffset(Position(-100 * deltaTime, 0.0f));
}
void runD(double deltaTime) {
	Player->addLocalPositionOffset(Position(100 * deltaTime, 0.0f));

}
void runQ(double deltaTime) {
	rotation -= 10 * deltaTime;
}
void runE(double deltaTime) {
	rotation += 10 * deltaTime;
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