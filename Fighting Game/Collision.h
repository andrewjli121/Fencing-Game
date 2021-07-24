#pragma once
#include "olcPixelGameEngine.h"
#include "fstream"

struct polygon {
	std::vector<olc::vf2d> p;
	olc::vi2d pos;
	float angle;
	std::vector<olc::vf2d> o;
	bool overlap = false;
};

class Collision{
private:

public:
	polygon quad;
	polygon quad2;
	static void getpoly(polygon& poly, std::fstream &file);
	static void makequad(polygon &quad);
	static void updatepoly(polygon& quad);
	static bool collision(polygon& r1, polygon& r2);
	static void drawpoly(polygon poly);
};

