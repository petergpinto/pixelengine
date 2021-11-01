#pragma once
#include "GameObject.h"
#include "texture.h"

class Player : public GameObject {
public:
	Player(Texture2D tex, SpriteRenderer* Renderer) : GameObject (tex, Renderer, Position(), Position(), Size(500.0f, 500.0f)) {

	}
	void moveLeft(double deltaTime) {
		this->localTransform.pos.x -= 100.0f * deltaTime;
	}
	void moveRight(double deltaTime) {
		this->localTransform.pos.x += 100.0f * deltaTime;
	}
	void moveUp(double deltaTime) {
		this->localTransform.pos.y -= 100.0f * deltaTime;
	}
	void moveDown(double deltaTime) {
		this->localTransform.pos.y += 100.0f * deltaTime;
	}
};