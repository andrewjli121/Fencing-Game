#include "StateController.h"

	State* currentState = nullptr;
	
	void StateController::Init() {
		currentState = new StateIdle();
	}

	void StateController::Update() {
		currentState->UpdateState();
	}

	void StateController::TransitionTo(std::string s) {
		delete currentState;

		if (s == "IDLE") {
			currentState = new StateIdle();
		}
		else if (s == "LEFT") {
			currentState = new StateWalkLeft();
		}
		else if (s == "RIGHT") {
			currentState = new StateWalkRight();
		}
	}

	StateController::~StateController() {
		delete currentState;
		std::cout << "State Destroyed";
	}