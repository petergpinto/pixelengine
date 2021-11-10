#include "Player.h"

Player::Player(std::shared_ptr<SpriteRenderer> rend, Texture2D tex, std::shared_ptr<Transform> anchorPoint) : GameObject(rend, tex, anchorPoint, Transform(Position(), Size(500.0f, 500.0f), Rotation())) {

}
void Player::moveLeft(double deltaTime) {
	this->localTransform.pos.x -= 100.0f * deltaTime;
}
void Player::moveRight(double deltaTime) {
	this->localTransform.pos.x += 100.0f * deltaTime;
}
void Player::moveUp(double deltaTime) {
	this->localTransform.pos.y -= 100.0f * deltaTime;
}
void Player::moveDown(double deltaTime) {
	this->localTransform.pos.y += 100.0f * deltaTime;
}

void Player::destroy(double deltaTime) {
	markedForDeletion = true;
}