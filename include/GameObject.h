#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "texture.h"
#include "SpriteRenderer.h"
#include "transform.h"


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