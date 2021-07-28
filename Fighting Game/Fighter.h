#pragma once
#include "olcPixelGameEngine.h"
#include "Collision.h"

class Fighter
{
private:
	polygon *center = new polygon;
	polygon *sword = new polygon;
public:
	olc::vf2d position = { 0.0f, 0.0f };
	std::vector<polygon*> hitBoxes{ center, sword };
	void linkFilesOne(std::vector<polygon*> hitBoxes);
	void linkFilesTwo(std::vector<polygon*> hitBoxes);
	int swordPos{ 1 };
	int lives{ 10 };
};

