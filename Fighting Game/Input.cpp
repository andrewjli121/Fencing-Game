#include "Input.h"

void Input::getInput(Fighter &f1, Fighter &f2, StateController *SC1, StateController *SC2, float fET) {
	//Move Player 1
	if (olc::Platform::ptrPGE->GetKey(olc::Key::LEFT).bHeld) {
		f1.position.x -= (1000 * fET);
		SC1->TransitionTo("LEFT");

	} else if (olc::Platform::ptrPGE->GetKey(olc::Key::RIGHT).bHeld) {
		f1.position.x += (1000 * fET);
		SC1->TransitionTo("RIGHT");

	} else if (olc::Platform::ptrPGE->GetKey(olc::Key::W).bPressed) {
		SC1->TransitionTo("UP");
		if(f1.swordPos < 2) f1.swordPos++;

	} else if (olc::Platform::ptrPGE->GetKey(olc::Key::S).bPressed) {
		SC1->TransitionTo("DOWN");
		if(f1.swordPos > 0) f1.swordPos--;

	} else {
		SC1->TransitionTo("IDLE");
	}

	//Move Player 2
	if (olc::Platform::ptrPGE->GetKey(olc::Key::A).bHeld) {
		f2.position.x -= (1000 * fET);
		SC2->TransitionTo("LEFT");
	}

	if (olc::Platform::ptrPGE->GetKey(olc::Key::D).bHeld) {
		f2.position.x += (1000 * fET);
		SC2->TransitionTo("RIGHT");
	}
}