//File to test rendering functions
//Should be excluded from final builds

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

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
std::unique_ptr<PixelEngine> engine;
std::shared_ptr<SpriteRenderer>  renderer;
std::shared_ptr<CellRenderer> cellrenderer;
void shutdown(double);
void createSpriteOnCursor(double);
void dragWorld(double);

int keyPressed = 0;
const char* glsl_version = "#version 330";

int RenderTest() {
	/* Initialize the library */
	engine = std::unique_ptr<PixelEngine>(new PixelEngine(false)); //std::make_unique causes assertion error if used here (wonder why?)

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
	renderer = std::shared_ptr<SpriteRenderer>(new SpriteRenderer(sprite));
	cellrenderer = std::shared_ptr<CellRenderer>(new CellRenderer(cell));
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(engine->getWindow(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	/* Loop until the user closes the window */
	while (!PixelEngine::shouldTerminate(engine->getWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(engine->getWindow(), &display_w, &display_h);

		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
	engine->terminate();
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