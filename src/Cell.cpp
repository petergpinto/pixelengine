#include "Cell.h"
#include <iostream>

Cell::Cell(std::shared_ptr<CellRenderer> rend, std::shared_ptr<Transform> anchorPoint, Position p) : GameObject(rend, Texture2D(), anchorPoint, Transform(p, Size(), Rotation()) ) {
	pos = p;
}

Cell::~Cell() {
	
}

void Cell::tick(double deltaTime) {
	pos.y += 100 * deltaTime;
}

void Cell::Render() {
	ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(this->pos.x-1, this->pos.y-1), ImVec2(this->pos.x + 1, this->pos.y + 1), IM_COL32(255, 0, 0, 200), 0, 10 + 4);
	Texture2D nulltex = Texture2D();
	//renderer->Draw(nulltex, glm::vec2(this->anchorPoint->pos.x + pos.x, this->anchorPoint->pos.y + pos.y), glm::vec2(1, 1),0.0f,glm::vec3(0,0,1));
}