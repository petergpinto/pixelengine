#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "texture.h"
#include "SpriteRenderer.h"
#include "transform.h"


class GameObject {
public:
	GameObject(Texture2D, Transform* anchorPoint, Transform objectTransform = Transform());
	virtual ~GameObject() = default;

	//Render functions
	void Render(SpriteRenderer*);
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

private:

};

class AnimatedGameObject : public GameObject {
public:
	AnimatedGameObject(std::vector<Texture2D>, Transform*);
	void Render(SpriteRenderer*);
private:
	std::vector<Texture2D> animationTextureSet;
	int currentAnimationTextureIndex;
};