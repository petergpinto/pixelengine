#include "GameObject.h"

GameObject::GameObject(Texture2D objectTexture, SpriteRenderer* Renderer, Position anchorPoint, Position pos, Size size) {
	this->activeTexture = objectTexture;
	this->renderer = Renderer;
	this->localTransform = Transform(pos,size);
}

GameObject::~GameObject() {

}

//Render functions
void GameObject::Render() {
	this->renderer->DrawSprite(this->activeTexture, 
		glm::vec2(this->anchorPoint.pos.x+this->localTransform.pos.x, this->anchorPoint.pos.y+this->localTransform.pos.y), 
		glm::vec2(this->localTransform.size.x, this->localTransform.size.y),
		0.0f, 
		glm::vec3(1.0f, 1.0f, 1.0f), 1.0f
	);
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
Transform GameObject::getAnchorPoint() {
	return this->anchorPoint;
}

void GameObject::setAnchorPoint(Position newAnchorPoint) {
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


AnimatedGameObject::AnimatedGameObject(std::vector<Texture2D> animationSet, SpriteRenderer* renderer) : GameObject(animationSet.at(0), renderer) {
	this->currentAnimationTextureIndex = 0;
	this->animationTextureSet = animationSet;
}

void AnimatedGameObject::Render() {
	this->activeTexture = this->animationTextureSet.at(this->currentAnimationTextureIndex);
	this->currentAnimationTextureIndex++;
	GameObject::Render();
}
