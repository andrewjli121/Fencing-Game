#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include "StateController.h"
#include "Camera.h"

class Game : public olc::PixelGameEngine
{
private:

	StateController *stateController = nullptr;
	Camera camera;

	olc::Sprite *playerOnePtr = nullptr;
	olc::Decal* playerOneDecal = nullptr;
	olc::Decal* playerTwoDecal = nullptr;
	//olc::vf2d position;

	//float fOffsetX = 0.0f;
	//float fOffsetY = 0.0f;
	//
	//float fStartPanX = 0.0f;
	//float fStartPanY = 0.0f;
	//
	//float fScaleX = 1.0f;
	//float fScaleY = 1.0f;

	//void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY) {
	//	nScreenX = (int)((fWorldX - fOffsetX) *fScaleX);
	//	nScreenY = (int)((fWorldY - fOffsetY) *fScaleY);
	//}
	//
	//void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY) {
	//	fWorldX = (float)(nScreenX) / fScaleX + fOffsetX;
	//	fWorldY = (float)(nScreenY) / fScaleY + fOffsetY;
	//}

public:

	~Game() {
		delete playerOnePtr;
		delete playerOneDecal;
		delete playerTwoDecal;
	}

	bool OnUserCreate() override {

		playerOnePtr = new olc::Sprite("Resources/fighter1.png");
		playerOneDecal = new olc::Decal(playerOnePtr);
		playerTwoDecal = new olc::Decal(playerOnePtr);

		stateController = new StateController;
		stateController->Init();

		//position.x = 0.0f;
		//position.y = 0.0f;

		camera.fOffsetX = -ScreenWidth() / 2;
		camera.fOffsetY = -ScreenHeight() / 2;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		//Get mouse coords
		float fMouseX = (float)GetMouseX();
		float fMouseY = (float)GetMouseY();

		//Pan
		//if (GetMouse(0).bPressed) {
		//	fStartPanX = fMouseX;
		//	fStartPanY = fMouseY;
		//}

		camera.MousePressed(fMouseX, fMouseY, GetMouse(0).bPressed);

		//if (GetMouse(0).bHeld) {
		//	fOffsetX -= (fMouseX - fStartPanX) / fScaleX;
		//	fOffsetY -= (fMouseY - fStartPanY) / fScaleY;
		//
		//	fStartPanX = fMouseX;
		//	fStartPanY = fMouseY;
		//}

		camera.MouseHeld(fMouseX, fMouseY, GetMouse(0).bHeld);

		//float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom;
		camera.ScreenToWorld(fMouseX, fMouseY, camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldY_BeforeZoom);

		//Scroll zoom
		//if (GetMouseWheel() > 0) {
		//	fScaleX *= 1.05f;
		//	fScaleY *= 1.05f;
		//} 
		//
		//if (GetMouseWheel() < 0) {
		//	fScaleX *= 0.95f;
		//	fScaleY *= 0.95f;
		//}

		camera.Zoom(GetMouseWheel());

		//float fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;
		camera.ScreenToWorld(fMouseX, fMouseY, camera.fMouseWorldX_AfterZoom, camera.fMouseWorldY_AfterZoom);
		camera.ChangeOffset(camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldX_AfterZoom);
		camera.ChangeOffset(camera.fMouseWorldY_BeforeZoom, camera.fMouseWorldY_AfterZoom);
		
		Clear(olc::BLACK);
		//int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

		//Move
		if (GetKey(olc::Key::LEFT).bHeld) {
			camera.position.x -= (100 *fElapsedTime);
			stateController->TransitionTo("LEFT");
		}

		if (GetKey(olc::Key::RIGHT).bHeld) {
			camera.position.x += (100 * fElapsedTime);
			stateController->TransitionTo("RIGHT");
		}

		if (GetKey(olc::Key::UP).bHeld) {
			camera.position.y -= (100 * fElapsedTime);
		}

		if (GetKey(olc::Key::DOWN).bHeld) {
			camera.position.y += (100 * fElapsedTime);
		}

		camera.WorldToScreen(camera.position.x, camera.position.y, camera.pixel_onex, camera.pixel_oney);
		camera.WorldToScreen(0, 0, camera.pixel_twox, camera.pixel_twoy);

		stateController->TransitionTo("IDLE");
		stateController->Update();

		SetPixelMode(olc::Pixel::MASK);
		DrawDecal(olc::vf2d(camera.pixel_onex + 100, camera.pixel_oney), playerOneDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		DrawDecal(olc::vf2d(camera.pixel_twox, camera.pixel_twoy), playerTwoDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		
		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};