#pragma once

#include "State.h"
#include "StateIdle.h"
#include "StateWalkLeft.h"
#include "StateWalkRight.h"


class StateController{
private:
	State* currentState;
public:
	void Init();
	void Update();
	void TransitionTo(std::string s);
	~StateController();
};

