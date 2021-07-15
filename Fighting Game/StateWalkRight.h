#pragma once
#include "State.h"

class StateWalkRight : public State {
public:
	StateWalkRight() {
		std::cout << "right";
	}
	void UpdateState() {
		std::cout << "right";
	}
};