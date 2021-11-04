#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "texture.h"
#include "SpriteRenderer.h"
#include "transform.h"
#include "Renderer.h"


class GameObject {
public:
	GameObject(Renderer* rend, Texture2D, Transform* anchorPoint, Transform objectTransform = Transform());
	virtual ~GameObject() = default;

	virtual void tick(double) {};

	//Render functions
	virtual void Render();
	bool isObjectVisible();
	void setObjectVisible(bool);

	//Position functions
	Transform* getAnchorPoint();
	void setAnchorPoint(Transform*);
	Transform getLocalTransform();
	void addLocalPositionOffset(Position);
	void setLocalPosition(Position);
	
	bool shouldDelete();

protected:
	Transform* anchorPoint;
	Transform localTransform;
	Texture2D activeTexture;
	bool drawObject;
	bool markedForDeletion;
	Renderer* renderer;
private:
	
};

class AnimatedGameObject : public GameObject {
public:
	AnimatedGameObject(SpriteRenderer*, std::vector<Texture2D>, Transform*);
	void Render();
private:
	std::vector<Texture2D> animationTextureSet;
	int currentAnimationTextureIndex;
};