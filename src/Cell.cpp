#include "Cell.h"

Cell::Cell(Transform* anchorPoint, Position p) : GameObject(Texture2D(), anchorPoint, Transform(p, Size(), Rotation()) ) {
	pos = p;
}

Cell::~Cell() {
	
}

void Cell::tick(double deltaTime) {
	pos.y -= 1 * deltaTime;
}

void Cell::Render(CellRenderer* renderer) {
	renderer->DrawCell(glm::vec2(pos.x, pos.y), glm::vec2(1, 1));
}