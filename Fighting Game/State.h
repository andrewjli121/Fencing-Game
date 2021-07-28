#pragma once
#include "olcPixelGameEngine.h"

class State {
private:
public:
	int swordPosition;
	virtual void UpdateState() = 0;
};


