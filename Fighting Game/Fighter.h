#pragma once
#include "olcPixelGameEngine.h"
#include "Collision.h"

class Fighter
{
private:

public:
	olc::vf2d position = { 0.0f, 0.0f };
	std::vector<polygon> hitBoxes;
};

