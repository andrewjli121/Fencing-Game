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
		else if (s == "LUNGE") {
			currentState = new StateLunge();
		}
		else if (s == "UP") {
			currentState = new StateIdle();
		}
		else if (s == "DOWN") {
			currentState = new StateIdle();
		}
		else if (s == "HIT") {
			currentState = new StateHit();
		}
}


	StateController::~StateController() {
		delete currentState;
		std::cout << "State Destroyed";
	}