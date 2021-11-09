#include "Action.h"

Action::Action(std::weak_ptr<GameObject> g, std::function<void(double)> f) {
	this->obj = g;
	this->func = f;
}

void Action::run(double deltaTime) {
	if (auto objPtr = this->obj.lock()) {
		func(deltaTime);
	}
	else {
		this->alive = false;
	}

}

bool Action::isAlive() {
	return this->alive;
}