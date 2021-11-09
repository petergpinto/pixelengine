#include "Cell.h"
#include <iostream>

Cell::Cell(CellRenderer* rend, std::shared_ptr<Transform> anchorPoint, Position p) : GameObject(rend, Texture2D(), anchorPoint, Transform(p, Size(), Rotation()) ) {
	pos = p;
}

Cell::~Cell() {
	
}

void Cell::tick(double deltaTime) {
	pos.y += 100 * deltaTime;
}

void Cell::Render() {
	Texture2D nulltex = Texture2D();
	renderer->Draw(nulltex, glm::vec2(this->anchorPoint->pos.x + pos.x, this->anchorPoint->pos.y + pos.y), glm::vec2(1, 1),0.0f,glm::vec3(0,0,1));
}