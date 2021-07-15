#pragma once
#include "State.h"

class StateWalkRight : public State {
public:
	void UpdateState() {
		std::cout << "right";
	}
};