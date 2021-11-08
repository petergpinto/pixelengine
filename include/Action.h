#pragma once

#include <functional>
#include "GameObject.h"

//An Action is a class which contains a weak_ptr to a GameObject and attempts to call 

class Action {
	
public:
	Action(std::weak_ptr<GameObject>, std::function<void(double)>);
	void run(double);

private:
	std::weak_ptr<GameObject> obj;
	std::function<void(double)> func;
	bool isAlive = true;
};