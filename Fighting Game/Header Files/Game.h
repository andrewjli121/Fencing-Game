#define OLC_PGE_APPLICATION 0
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

		return true;
	}

	void run() {

	}
};