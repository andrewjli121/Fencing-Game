#pragma once
#include "State.h"

class WalkRight : public State {
public:
	void UpdateState() {
		std::cout << "right";
	}
};