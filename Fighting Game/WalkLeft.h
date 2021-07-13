#pragma once
#include "State.h"

class WalkLeft : public State {
public:
	void UpdateState() override {
		std::cout << "left";
	}
};
