#pragma once
#include "GameObject.h"
#include "texture.h"

class Player : public GameObject {
public:
	Player(SpriteRenderer*, Texture2D, Transform*);
	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);
	void destroy(double);
};
