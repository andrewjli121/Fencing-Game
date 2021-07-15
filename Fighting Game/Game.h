#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include "StateController.h"

class Game : public olc::PixelGameEngine
{
private:

	olc::Sprite *playerOnePtr = nullptr;
	olc::Decal* playerOneDecal = nullptr;
	olc::Decal* playerTwoDecal = nullptr;
	olc::vf2d position;

	float fOffsetX = 0.0f;
	float fOffsetY = 0.0f;

	float fStartPanX = 0.0f;
	float fStartPanY = 0.0f;

	float fScaleX = 1.0f;
	float fScaleY = 1.0f;

	void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY) {
		nScreenX = (int)((fWorldX - fOffsetX) *fScaleX);
		nScreenY = (int)((fWorldY - fOffsetY) *fScaleY);
	}

	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY) {
		fWorldX = (float)(nScreenX) / fScaleX + fOffsetX;
		fWorldY = (float)(nScreenY) / fScaleY + fOffsetY;
	}

public:

	~Game() {
		delete playerOnePtr;
		delete playerOneDecal;
		delete playerTwoDecal;
	}

	bool OnUserCreate() override {

		StateController sController;
		sController.Init();

		playerOnePtr = new olc::Sprite("Resources/fighter1.png");
		playerOneDecal = new olc::Decal(playerOnePtr);
		playerTwoDecal = new olc::Decal(playerOnePtr);
		position.x = 0.0f;
		position.y = 0.0f;

		fOffsetX = -ScreenWidth() / 2;
		fOffsetY = -ScreenHeight() / 2;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		//Get mouse coords
		float fMouseX = (float)GetMouseX();
		float fMouseY = (float)GetMouseY();

		//Pan
		if (GetMouse(0).bPressed) {
			fStartPanX = fMouseX;
			fStartPanY = fMouseY;
		}

		if (GetMouse(0).bHeld) {
			fOffsetX -= (fMouseX - fStartPanX) / fScaleX;
			fOffsetY -= (fMouseY - fStartPanY) / fScaleY;

			fStartPanX = fMouseX;
			fStartPanY = fMouseY;
		}

		float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom;
		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom);

		//Scroll zoom
		if (GetMouseWheel() > 0) {
			fScaleX *= 1.05f;
			fScaleY *= 1.05f;
		} 
		
		if (GetMouseWheel() < 0) {
			fScaleX *= 0.95f;
			fScaleY *= 0.95f;
		}


		float fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;
		ScreenToWorld(fMouseX, fMouseY, fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom);
		fOffsetX += (fMouseWorldX_BeforeZoom - fMouseWorldX_AfterZoom);
		fOffsetY += (fMouseWorldY_BeforeZoom - fMouseWorldY_AfterZoom);
		
		Clear(olc::BLACK);
		int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

		//Move
		if (GetKey(olc::Key::LEFT).bHeld) {
			position.x -= (100 *fElapsedTime);
		}

		if (GetKey(olc::Key::RIGHT).bHeld) {
			position.x += (100 * fElapsedTime);
		}

		if (GetKey(olc::Key::UP).bHeld) {
			position.y -= (100 * fElapsedTime);
		}

		if (GetKey(olc::Key::DOWN).bHeld) {
			position.y += (100 * fElapsedTime);
		}

		WorldToScreen(position.x, position.y, pixel_sx, pixel_sy);
		WorldToScreen(0, 0, pixel_ex, pixel_ey);

		SetPixelMode(olc::Pixel::MASK);
		DrawDecal(olc::vf2d(pixel_sx, pixel_sy), playerOneDecal, olc::vf2d(fScaleX, fScaleY));
		//DrawDecal(olc::vf2d(pixel_ex, pixel_ey), playerTwoDecal, olc::vf2d(fScaleX, fScaleY));
		
		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};