#include "Action.h"

Action::Action(std::weak_ptr<GameObject> g, std::function<void(double)> f) {
	this->obj = g;
	this->func = f;
}

Action::run(double deltaTime) {
	if (auto objPtr = this->obj.lock()) {
		std::function<void(double)> f = std::bind(&func, objPtr.get(), std::placeholders::_1);
		f(deltaTime);
	}
	else {
		this->isAlive = false;
	}

}