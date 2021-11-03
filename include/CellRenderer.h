#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "Renderer.h"

class CellRenderer : public Renderer {
	
public:
	CellRenderer(Shader &shader);
	~CellRenderer();

	void DrawCell(glm::vec2 position, glm::vec2 size = glm::vec2(1.0f, 1.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), float aspectRatio = 1.0f);
private:
	
	// Render state
	Shader       shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();

};