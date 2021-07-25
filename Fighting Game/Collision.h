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
	static void getpoly(polygon& poly, std::fstream &file);
	static void updatepoly(polygon& quad, int camx, int camy, float scale);
	static bool collision(polygon& r1, polygon& r2);
	static void allCollision(std::vector<polygon*> f1, std::vector<polygon*> f2);
	static void drawpoly(polygon poly);
};

