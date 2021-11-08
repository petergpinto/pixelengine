#include "GameObject.h"

GameObject::GameObject(Renderer* rend, Texture2D objectTexture, Transform* anchorPoint, Transform objectTransform) {
	this->activeTexture = objectTexture;
	this->localTransform = objectTransform;
	this->anchorPoint = anchorPoint;
	markedForDeletion = false;
	renderer = rend;
}

//Render functions
void GameObject::Render() {
	//Call the renderer, which is a derived Renderer, Draw is a virtual function that is part of Renderer
	renderer->Draw(this->activeTexture, 
		glm::vec2(this->anchorPoint->pos.x + this->localTransform.pos.x, this->anchorPoint->pos.y+this->localTransform.pos.y), 
		glm::vec2(this->localTransform.size.x, this->localTransform.size.y),
		0.0f, 
		glm::vec3(1.0f, 1.0f, 1.0f), 
		1.0f
	);
}

bool GameObject::isObjectVisible() {
	return this->drawObject;
}

void GameObject::setObjectVisible(bool objectVisible) {
	this->drawObject = objectVisible;
}

//Position functions
Transform* GameObject::getAnchorPoint() {
	return (this->anchorPoint);
}

void GameObject::setAnchorPoint(Transform* newAnchorPoint) {
	this->anchorPoint = newAnchorPoint;
}

Transform GameObject::getLocalTransform() {
	return this->localTransform;
}

void GameObject::addLocalPositionOffset(Position offset) {
	this->localTransform.pos += offset;
}

void GameObject::setLocalPosition(Position newPosition) {
	this->localTransform.pos = newPosition;
}

bool GameObject::shouldDelete() {
	return this->markedForDeletion;
}


AnimatedGameObject::AnimatedGameObject(SpriteRenderer* rend, std::vector<Texture2D> animationSet, Transform* anchorPoint) : GameObject(rend, animationSet.at(0), anchorPoint) {
	this->currentAnimationTextureIndex = 0;
	this->animationTextureSet = animationSet;
}

void AnimatedGameObject::Render() {
	this->activeTexture = this->animationTextureSet.at(this->currentAnimationTextureIndex);
	this->currentAnimationTextureIndex++;
	GameObject::Render();
}
