#pragma once
#include "olcPixelGameEngine.h"

struct polygon {
	std::vector<olc::vf2d> p;
	olc::vi2d pos;
	float angle;
	std::vector<olc::vf2d> o;
	bool overlap = false;
};

class Collision
{
private:

public:
	polygon quad;
	void makequad(polygon &quad);
};

