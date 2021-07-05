#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>

class Game : public olc::PixelGameEngine
{
private:

public:

	bool OnUserCreate() override {

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		for (float y = 0.0; y <= 10.0f; y++) {

			float sx = 0.0f, sy = y;
			float ex = 10.0f, ey = y;
		}
		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};