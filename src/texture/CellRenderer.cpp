#include "CellRenderer.h"

CellRenderer::CellRenderer(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

CellRenderer::~CellRenderer()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void CellRenderer::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void CellRenderer::SetProjectionMatrix(glm::mat4 matrix) {
	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, false, glm::value_ptr(matrix));
}

void CellRenderer::DrawCell(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, float aspectRatio)
{

	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position.x - (size.x / 2), position.y - (size.y / 2), 0.0f));  //First translation, move the center of the sprite to 'position'

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f)); // last scale

	this->shader.SetMatrix4("model", model);

	// render textured quad

	this->shader.SetVector3f("spriteColor", color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}