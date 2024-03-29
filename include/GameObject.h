#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>
#include "texture.h"
#include "SpriteRenderer.h"
#include "transform.h"
#include "Renderer.h"

//GameObject is a base class which others may inherit from
class GameObject {
public:
	GameObject(std::shared_ptr<Renderer> rend, Texture2D, std::shared_ptr<Transform> anchorPoint, Transform objectTransform = Transform());
	virtual ~GameObject() = default;

	virtual void tick(double) {};

	//Render functions
	virtual void Render(); //Use the renderer to render the GameObject
	bool isObjectVisible(); //Is the object being drawn?
	void setObjectVisible(bool); //Set whether or not the object is drawn

	//Position functions
	std::shared_ptr<Transform> getAnchorPoint(); //Return a pointer to the anchorpoint for the GameObject
	void setAnchorPoint(std::shared_ptr<Transform>); //Set a new anchor point
	Transform getLocalTransform(); //Get the transform in relation to the anchorpoint
	void addLocalPositionOffset(Position); //Add Position to localTransform.pos
	void setLocalPosition(Position); //Set a new localTransform.pos
	
	bool shouldDelete();

protected:
	std::shared_ptr<Transform> anchorPoint; //Pointer to the GameObject's anchor point
	Transform localTransform; 
	Texture2D activeTexture; //Texture to draw on the GameObject, may be null for some
	bool drawObject; //Do we draw the object?
	bool markedForDeletion; //Is this object going to be deleted? (maybe deprecated)
	std::shared_ptr<Renderer> renderer;
private:
	
};

//An inherited member from GameObject that supports multiple textures in an animation set
class AnimatedGameObject : public GameObject {
public:
	AnimatedGameObject(std::shared_ptr<SpriteRenderer>, std::vector<Texture2D>, std::shared_ptr<Transform>);
	void Render();
private:
	std::vector<Texture2D> animationTextureSet;
	int currentAnimationTextureIndex;
};