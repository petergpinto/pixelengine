#pragma once
#include "GameObject.h"
#include "texture.h"

class Player : public GameObject {
public:
	Player(Texture2D, SpriteRenderer*);
	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);
};
