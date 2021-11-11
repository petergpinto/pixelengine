#pragma once

#include "GameObject.h"
#include "CellRenderer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class Cell : public GameObject {

public:
	Cell(std::shared_ptr<CellRenderer>, std::shared_ptr<Transform>,	Position);
	~Cell();
	void tick(double);
	void Render();

private:
	Position pos;
};