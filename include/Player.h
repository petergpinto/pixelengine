#pragma once
#include "GameObject.h"
#include "texture.h"

class Player : public GameObject {
public:
	Player(std::shared_ptr<SpriteRenderer>, Texture2D, std::shared_ptr<Transform>);
	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);
	void destroy(double);
};
