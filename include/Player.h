#pragma once
#include "GameObject.h"
#include "texture.h"

class Player : public GameObject {
public:
	Player(Texture2D);
	void moveLeft(double);
	void moveRight(double);
	void moveUp(double);
	void moveDown(double);
	void destroy(double);
};
