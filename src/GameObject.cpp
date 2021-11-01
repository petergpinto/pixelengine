#include "GameObject.h"

GameObject::GameObject(Texture2D objectTexture, Position anchorPoint, Position pos, Size size) {
	this->activeTexture = objectTexture;
	this->localTransform = Transform(pos,size);
	this->anchorPoint = Transform(anchorPoint, Size(), Rotation());
	markedForDeletion = false;
}

GameObject::~GameObject() {

}

//Render functions
void GameObject::Render(SpriteRenderer* renderer) {
	renderer->DrawSprite(this->activeTexture, 
		glm::vec2(this->anchorPoint.pos.x+this->localTransform.pos.x, this->anchorPoint.pos.y+this->localTransform.pos.y), 
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

bool GameObject::shouldDelete() {
	return this->markedForDeletion;
}


AnimatedGameObject::AnimatedGameObject(std::vector<Texture2D> animationSet) : GameObject(animationSet.at(0)) {
	this->currentAnimationTextureIndex = 0;
	this->animationTextureSet = animationSet;
}

void AnimatedGameObject::Render(SpriteRenderer* renderer) {
	this->activeTexture = this->animationTextureSet.at(this->currentAnimationTextureIndex);
	this->currentAnimationTextureIndex++;
	GameObject::Render(renderer);
}
