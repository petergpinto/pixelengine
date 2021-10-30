#include "GameObject.h"

GameObject::GameObject(Texture2D objectTexture, SpriteRenderer* Renderer, Position anchorPoint, Position pos, Size size) {
	this->activeTexture = objectTexture;
	this->renderer = Renderer;
	this->size = size;
	this->localPosition = pos;
}

GameObject::~GameObject() {

}

//Render functions
void GameObject::Render() {
	this->renderer->DrawSprite(this->activeTexture, glm::vec2(this->anchorPoint.x+this->localPosition.x, this->anchorPoint.y+this->localPosition.y), glm::vec2(this->size.x, this->size.y), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
}

void GameObject::setRenderer(SpriteRenderer* newRenderer) {
	this->renderer = newRenderer;
}

bool GameObject::isObjectVisible() {
	return this->drawObject;
}

void GameObject::setObjectVisible(bool objectVisible) {
	this->drawObject = objectVisible;
}

//Position functions
Position GameObject::getAnchorPoint() {
	return this->anchorPoint;
}

void GameObject::setAnchorPoint(Position newAnchorPoint) {
	this->anchorPoint = newAnchorPoint;
}

Position GameObject::getLocalPosition() {
	return this->localPosition;
}

void GameObject::addLocalPositionOffset(Position offset) {
	this->localPosition += offset;
}

void GameObject::setLocalPosition(Position newPosition) {
	this->localPosition = newPosition;
}


AnimatedGameObject::AnimatedGameObject(std::vector<Texture2D> animationSet, SpriteRenderer* renderer) : GameObject(animationSet.at(0), renderer) {
	this->currentAnimationTextureIndex = 0;
	this->animationTextureSet = animationSet;
}

void AnimatedGameObject::Render() {
	this->activeTexture = this->animationTextureSet.at(this->currentAnimationTextureIndex);
	this->currentAnimationTextureIndex++;
	GameObject::Render();
}
