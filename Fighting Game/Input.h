#pragma once
#include "olcPixelGameEngine.h"
#include "StateController.h"
#include "Fighter.h"

class Input
{
private:
	
public:
	static void getInput(Fighter &f1, Fighter &f2, StateController *SC1, StateController *SC2, float fET);
};

