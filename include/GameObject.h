#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "texture.h"
#include "SpriteRenderer.h"

struct Position {
	double x;
	double y;
	Position(double x = 0.0f, double y = 0.0f)
		: x(x), y(y)
	{
	}

	Position& operator=(const Position& a) {
		x = a.x;
		y = a.y;
		return *this;
	}

	Position operator+(const Position& a) const {
		return Position(a.x + x, a.y + y);
	}

	Position& operator+=(const Position& a) {
		x = a.x+x;
		y = a.y+y;
		return *this;
	}
};

struct Size {
	double x;
	double y;
	Size(double x = 100.0f, double y = 100.0f)
		: x(x), y(y)
	{
	}
	Size& operator=(const Position& a) {
		x = a.x;
		y = a.y;
		return *this;
	}

	Size operator+(const Position& a) const {
		return Size(a.x + x, a.y + y);
	}

	Size& operator+=(const Position& a) {
		x = a.x + x;
		y = a.y + y;
		return *this;
	}
};

class GameObject {
public:
	GameObject(Texture2D, SpriteRenderer*, Position anchorPoint = Position(), Position pos = Position(), Size size = Size());
	~GameObject();

	//Render functions
	void setRenderer(SpriteRenderer*);
	void Render();
	bool isObjectVisible();
	void setObjectVisible(bool);

	//Position functions
	Position getAnchorPoint();
	void setAnchorPoint(Position);
	Position getLocalPosition();
	void addLocalPositionOffset(Position);
	void setLocalPosition(Position);

protected:
	Position anchorPoint;
	Position localPosition;
	Size size;
	Texture2D activeTexture;
	bool drawObject;
	SpriteRenderer* renderer;

private:

};

class AnimatedGameObject : public GameObject {
public:
	AnimatedGameObject(std::vector<Texture2D>, SpriteRenderer*);
	void Render();
private:
	std::vector<Texture2D> animationTextureSet;
	int currentAnimationTextureIndex;
};