#pragma once

#include "GameObject.h"
#include "CellRenderer.h"

class Cell : public GameObject {

public:
	Cell(Transform*, Position);
	~Cell();
	void tick(double);
	void Render(CellRenderer*);

private:
	Position pos;
};