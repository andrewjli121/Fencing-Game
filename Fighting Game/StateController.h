#pragma once

#include "State.h"
#include "StateIdle.h"
#include "StateWalkLeft.h"

class StateController{
private:
	State* currentState;
public:
	void Init();
	void Update();
	~StateController();
};

