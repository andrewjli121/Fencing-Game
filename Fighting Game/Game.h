#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>

class Game : public olc::PixelGameEngine
{
private:
	olc::Sprite* spritePtr = nullptr;
	olc::Decal* decalPtr = nullptr;

public:
	~Game()
	{
		delete spritePtr;
	}



	bool OnUserCreate() override {

		spritePtr = new olc::Sprite("smiley.png");
		decalPtr = new olc::Decal(spritePtr);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		Clear(olc::DARK_BLUE);

		olc::vf2d position(10, 50);
		DrawDecal(position, decalPtr);

		olc::vf2d stringposition(0, 0);
		DrawString(stringposition, "test", olc::DARK_RED);

		return true;
	}

	void run() {
		if (Construct(600, 300, 2, 2)) {
			Start();
		}
	}
};