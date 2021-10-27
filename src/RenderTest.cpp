//File to test rendering functions
//Should be excluded from final builds

#include "RenderTest.h"
#include "KeyboardHandler.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
float xPos, yPos, deltaTime, rotation;
void runW();
void runA();
void runS();
void runD();
void runQ();
void runE();

int keyPressed = 0;

int RenderTest() {
	/* Initialize the library */
	PixelEngine* engine = new PixelEngine(false);

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

	//glfwSetKeyCallback(engine->getWindow(), key_callback);

	glViewport(0, 0, engine->getWidth(), engine->getHeight());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SpriteRenderer  *Renderer;
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

	/* Loop until the user closes the window */
	while (!PixelEngine::shouldTerminate(engine->getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//std::cout << deltaTime << std::endl;
		engine->fpsCounter(deltaTime, 100);
		keyboardHandler->handleInput();

		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Texture2D faceHighRes = ResourceManager::GetTexture("faceHighRes");
		Renderer->DrawSprite(faceHighRes,
			glm::vec2(static_cast<float>(engine->getWidth() / 2), static_cast<float>(engine->getHeight() / 2)), glm::vec2(500.0f, 500.0f), -15.0f, glm::vec3(0.0f, 1.0f, 1.0f));
		Texture2D test = ResourceManager::GetTexture("test");
		Renderer->DrawSprite(test,
			glm::vec2(0.0f, 0.0f), glm::vec2(500.0f, 500.0f), 45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		Texture2D face = ResourceManager::GetTexture("face");
		Renderer->DrawSprite(face,
			glm::vec2(xPos, yPos), glm::vec2(500.0f, 500.0f), rotation, glm::vec3(1.0f, 1.0f, 1.0f));

		//static_cast<float>(engine->getWidth() /2), static_cast<float>(engine->getHeight() / 2)
	/* Swap front and back buffers */
		engine->swapBufferOrFlush();

		/* Poll for and process events */
		glfwPollEvents();
		switch (keyPressed) {
		case GLFW_KEY_D:
			xPos += 100 * deltaTime;
			break;
		case GLFW_KEY_A:
			xPos -= 100 * deltaTime;
			break;
		case GLFW_KEY_S:
			yPos += 100 * deltaTime;
			break;
		case GLFW_KEY_W:
			yPos -= 100 * deltaTime;
			break;
		case GLFW_KEY_Q:
			rotation += 10 * deltaTime;
			break;
		case GLFW_KEY_E:
			rotation -= 10 * deltaTime;
			break;
		}
	}

	glfwTerminate();
	return 0;
}

void runW() {
	yPos -= 100 * deltaTime;
}
void runA() {
	xPos -= 100 * deltaTime;
}
void runS() {
	yPos += 100 * deltaTime;
}
void runD() {
	xPos += 100 * deltaTime;
}
void runQ() {
	rotation -= 10 * deltaTime;
}
void runE() {
	rotation += 10 * deltaTime;
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