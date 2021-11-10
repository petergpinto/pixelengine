#pragma once

#include "GameObject.h"
#include "CellRenderer.h"

class Cell : public GameObject {

public:
	Cell(CellRenderer*, std::shared_ptr<Transform>,	Position);
	~Cell();
	void tick(double);
	void Render();

private:
	Position pos;
};