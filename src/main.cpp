// main.cpp : Defines the entry point for the application.
//

#include "main.h"
#include "PixelEngine.h"
#include <fstream>

int main(void)
{
	/* Initialize the library */
	PixelEngine* engine = new PixelEngine();
	
	if (engine->checkError() != ERROR::NONE) {
		engine->terminate();
		return engine->checkError();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(engine->getWindow());
	gladLoadGL(glfwGetProcAddress); //Prevents memory access violation https://stackoverflow.com/questions/67400482/access-violation-executing-location-0x0000000000000000-opengl-with-glad-and-glf

	glViewport(0,0,engine->getHeight(), engine->getWidth());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SpriteRenderer  *Renderer;
	ResourceManager::LoadShader("../resources/shaders/sprite.vs", "../resources/shaders/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho<float>(0.0f, static_cast<float>(engine->getWidth()),
		static_cast<float>(engine->getHeight()), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	Shader sprite = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(sprite);

	ResourceManager::LoadTexture("../resources/textures/awesomeface.png", true, "face");

	/* Loop until the user closes the window */
	while (!PixelEngine::shouldTerminate(engine->getWindow()))
	{
		/* Render here */
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Texture2D face = ResourceManager::GetTexture("face");
		Renderer->DrawSprite(face,
			glm::vec2(static_cast<float>(engine->getWidth()-300), static_cast<float>(engine->getHeight()-400)), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		/* Swap front and back buffers */
		glfwSwapBuffers(engine->getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int WinMain(void) {
	main();
}
