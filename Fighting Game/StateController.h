#pragma once

#include "State.h"
#include "StateIdle.h"
#include "StateWalkLeft.h"
#include "StateWalkRight.h"
#include "StateLunge.h"
#include "Fighter.h"
#include "StateHit.h"

class StateController{
private:
	//std::string change;
public:
	State* currentState;
	std::string change;
	void Init();
	void Update();
	void TransitionTo(std::string s);
	~StateController();
};

