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

public:

	~Game() {
		delete playerOnePtr;
		delete playerOneDecal;
		delete playerTwoDecal;
	}

	bool OnUserCreate() override {

		//Sprite ptrs
		playerOnePtr = new olc::Sprite("Resources/fighter1.png");
		playerOneDecal = new olc::Decal(playerOnePtr);
		playerTwoDecal = new olc::Decal(playerOnePtr);

		//State referencing/obj
		stateController = new StateController;
		stateController->Init();

		//Default offset
		camera.fOffsetX = -ScreenWidth() * 0.50;
		camera.fOffsetY = -ScreenHeight() * 0.55;
		camera.position.x = -playerOnePtr->width / 2;
		camera.position.y = -playerOnePtr->width / 2;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		//Get mouse coords
		float fMouseX = (float)GetMouseX();
		float fZeroX = (float)ScreenWidth() * 0.50;
		float fZeroY = (float)ScreenHeight() * 0.90;
		float fMouseY = (float)GetMouseY();

		if(GetMouse(0).bPressed)	camera.MousePressed(fMouseX, fZeroY);

		if(GetMouse(0).bHeld)	camera.MouseHeld(fMouseX, fZeroY);

		camera.ScreenToWorld(fZeroX, fZeroY, camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldY_BeforeZoom);
		camera.Zoom(GetMouseWheel());
		camera.ScreenToWorld(fZeroX, fZeroY, camera.fMouseWorldX_AfterZoom, camera.fMouseWorldY_AfterZoom);
		camera.ChangeOffset(camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldX_AfterZoom, true);
		camera.ChangeOffset(camera.fMouseWorldY_BeforeZoom, camera.fMouseWorldY_AfterZoom, false);
		
		Clear(olc::BLACK);

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
		
		//Coords after movement
		camera.WorldToScreen(camera.position.x, camera.position.y, camera.pixel_onex, camera.pixel_oney);
		camera.WorldToScreen(0, 0, camera.pixel_twox, camera.pixel_twoy);

		//Transition State
		stateController->TransitionTo("IDLE");
		stateController->Update();

		//Draw Decals
		SetPixelMode(olc::Pixel::MASK);
		FillCircle(600, 540, 2, olc::YELLOW);
		DrawDecal(olc::vf2d(camera.pixel_onex, camera.pixel_oney), playerOneDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		DrawDecal(olc::vf2d(camera.pixel_twox, camera.pixel_twoy), playerTwoDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};