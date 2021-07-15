#pragma once
#include "State.h"

class StateIdle : public State {
public:
	StateIdle() {
		std::cout << "Idle";
	}

	void UpdateState() override {
		std::cout << "idle";
	}
};
