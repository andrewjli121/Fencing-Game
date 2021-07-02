#define OLC_PGE_APPLICATION 0
#pragma once

#include "olcPixelGameEngine.h"

class Game : olc::PixelGameEngine{

public:
	bool OnUserCreate() override {

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		return true;
	}

	void run() {
		if (Construct(600, 300, 2, 2)) {
			Start();
		}
	}
};