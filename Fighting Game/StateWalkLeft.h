#pragma once
#include "State.h"

class StateWalkLeft : public State {
public:
	void UpdateState() override {
		std::cout << "left";
	}
};
