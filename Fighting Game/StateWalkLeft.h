#pragma once
#include "State.h"

class StateWalkLeft : public State {
public:
	StateWalkLeft() {
		std::cout << "left";
	}
	void UpdateState() override {

	}
};
