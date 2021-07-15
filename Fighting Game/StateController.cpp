#include "StateController.h"

	State* currentState = nullptr;
	
	void StateController::Init() {
		currentState = new StateIdle();
	}

	void StateController::Update() {
		currentState->UpdateState();
	}

	StateController::~StateController() {
		delete currentState;
	}