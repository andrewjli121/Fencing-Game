#pragma once
#include "olcPixelGameEngine.h"
#include "Collision.h"

class Fighter
{
private:
	polygon *center = new polygon;
	polygon *rLeg = new polygon;
	polygon *lLeg = new polygon;
	polygon *head = new polygon;
	polygon *rArm = new polygon;
	polygon *lArm = new polygon;
	
public:
	olc::vf2d position = { 0.0f, 0.0f };
	std::vector<polygon*> hitBoxes{ center, head, lArm, lLeg, rArm, rLeg };
	void linkFiles(std::vector<polygon*> hitBoxes, Fighter fighter);
};

