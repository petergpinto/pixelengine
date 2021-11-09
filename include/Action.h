#pragma once

#include <functional>
#include <memory>
#include "GameObject.h"

//An Action is a class which contains a weak_ptr to a GameObject and attempts to call a function on it
//func should be the result to a std::bind(&, GameObject*, placeholder::_1)
//before calling func, we test if obj exists using the weak_ptr, once its locked and we know it exists, func can be called

class Action {
	
public:
	Action(std::weak_ptr<GameObject>, std::function<void(double)>);
	void run(double);
	bool isAlive();

private:
	std::weak_ptr<GameObject> obj;
	std::function<void(double)> func;
	bool alive = true;
};