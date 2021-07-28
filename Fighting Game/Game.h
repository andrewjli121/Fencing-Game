#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include "StateController.h"
#include "Camera.h"
#include "Fighter.h"
#include "Collision.h"
#include "Input.h"

class Game : public olc::PixelGameEngine
{
private:

	StateController* stateController1 = nullptr;
	StateController* stateController2 = nullptr;
	Fighter fighter1;
	Fighter fighter2;
	Camera camera;

	olc::Sprite* playerOnePtr = nullptr;
	olc::Sprite* playerTwoPtr = nullptr;
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
		playerOnePtr = new olc::Sprite("Resources/1IdleMid.png");
		playerTwoPtr = new olc::Sprite("Resources/2IdleMid.png");
		playerOneDecal = new olc::Decal(playerOnePtr);
		playerTwoDecal = new olc::Decal(playerTwoPtr);

		//State referencing/obj
		stateController1 = new StateController;
		stateController1->Init();
		stateController2 = new StateController;
		stateController2->Init();

		//Default offset
		camera.fOffsetX = -ScreenWidth() * 0.50;
		camera.fOffsetY = -ScreenHeight() * 0.70;
		fighter1.position.x = -playerOnePtr->width / 2 - 400;
		fighter1.position.y = -playerOnePtr->height / 2;
		fighter2.position.x = -playerTwoPtr->width / 2 + 400;
		fighter2.position.y = -playerTwoPtr->height / 2;

		fighter1.linkFilesOne(fighter1.hitBoxes);
		fighter2.linkFilesTwo(fighter2.hitBoxes);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		//Get mouse coords
		float fMouseX = (float)GetMouseX();
		float fZeroX = (float)ScreenWidth() * 0.50;
		float fZeroY = (float)ScreenHeight() * 0.90;
		float fMouseY = (float)GetMouseY();
		
		//Mouse Pan
		if (GetMouse(0).bPressed)	camera.MousePressed(fMouseX, fZeroY);
		if (GetMouse(0).bHeld)	camera.MouseHeld(fMouseX, fZeroY);

		camera.ScreenToWorld(fZeroX, fZeroY, camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldY_BeforeZoom);
		camera.ZoomBig(GetMouseWheel());
		camera.ScreenToWorld(fZeroX, fZeroY, camera.fMouseWorldX_AfterZoom, camera.fMouseWorldY_AfterZoom);
		camera.ChangeOffset(camera.fMouseWorldX_BeforeZoom, camera.fMouseWorldX_AfterZoom, true);
		camera.ChangeOffset(camera.fMouseWorldY_BeforeZoom, camera.fMouseWorldY_AfterZoom, false);

		Clear(olc::WHITE);

		//Transition State
		stateController1->TransitionTo("IDLE");
		stateController2->TransitionTo("IDLE");
		Input::getInput(fighter1, fighter2, stateController1, stateController2, fElapsedTime);
		stateController1->Update();
		stateController2->Update();

		//Coords after movement
		camera.WorldToScreen(fighter1.position.x, fighter1.position.y, camera.pixel_onex, camera.pixel_oney);
		camera.WorldToScreen(fighter2.position.x, fighter2.position.y, camera.pixel_twox, camera.pixel_twoy);
		float leftMost = ScreenWidth() * 0.10;
		float rightMost = ScreenWidth() * 0.90;
		float pOneMP{ (camera.pixel_onex + (playerOnePtr->width / 2 * camera.fScaleX)) };
		float pTwoMP{ (camera.pixel_twox + (playerTwoPtr->width / 2 * camera.fScaleX)) };

		//Dyanmic zoom in
		while ((pOneMP > leftMost && camera.fScaleX < 0.5) 	|| (pTwoMP < rightMost && camera.fScaleX < 0.5)) {
			camera.WorldToScreen(fighter1.position.x, fighter1.position.y, camera.pixel_onex, camera.pixel_oney);
			camera.WorldToScreen(fighter2.position.x, fighter2.position.y, camera.pixel_twox, camera.pixel_twoy);
			camera.DynamicZoom(fZeroX, fZeroY, 1);
			pOneMP = (camera.pixel_onex + (playerOnePtr->width / 2 * camera.fScaleX));
			pTwoMP = (camera.pixel_twox + (playerTwoPtr->width / 2 * camera.fScaleX));
		}

		//Dynamic zoom out
		while ((pOneMP < leftMost || pOneMP > rightMost) || (pTwoMP > rightMost || pTwoMP < leftMost)) {
			camera.WorldToScreen(fighter1.position.x, fighter1.position.y, camera.pixel_onex, camera.pixel_oney);
			camera.WorldToScreen(fighter2.position.x, fighter2.position.y, camera.pixel_twox, camera.pixel_twoy);
			camera.DynamicZoom(fZeroX, fZeroY, -1);
			pOneMP = (camera.pixel_onex + (playerOnePtr->width / 2 * camera.fScaleX));
			pTwoMP = (camera.pixel_twox + (playerTwoPtr->width / 2 * camera.fScaleX));
		}

		//Draw Decals
		SetPixelMode(olc::Pixel::MASK);
		FillCircle(600, 540, 2, olc::YELLOW);
		DrawDecal(olc::vf2d(camera.pixel_onex, camera.pixel_oney), playerOneDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		DrawDecal(olc::vf2d(camera.pixel_twox, camera.pixel_twoy), playerTwoDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		
		//Boxes
		for (auto *a : fighter1.hitBoxes) {
			Collision::updatepoly(*a, camera.pixel_onex, camera.pixel_oney, camera.fScaleX);
		}
		for (auto *a : fighter2.hitBoxes) {
			Collision::updatepoly(*a, camera.pixel_twox, camera.pixel_twoy, camera.fScaleX);
		}

		Collision::allCollision(fighter1.hitBoxes, fighter2.hitBoxes);

		//Lives F1
		for (int i = 0; i < fighter1.hitBoxes.size(); i++) {
			Collision::drawpoly(*fighter1.hitBoxes[i]);
			static bool change = false;
			if (fighter1.hitBoxes[0]->overlap && !change) {
				stateController1->TransitionTo("HIT");
				change = true;
				fighter1.lives--;
			}
			if (!fighter1.hitBoxes[0]->overlap && change) {
				change = false;
			}
		}
		//Lives F2
		for (int i = 0; i < fighter2.hitBoxes.size(); i++) {
			Collision::drawpoly(*fighter2.hitBoxes[i]);
			static bool change = false;
			if (fighter2.hitBoxes[0]->overlap && !change) {
				stateController2->TransitionTo("HIT");
				change = true;
				fighter2.lives--;
			}
			if (!fighter2.hitBoxes[0]->overlap && change) {
				change = false;
			}
		}
		
		DrawString(10,10, "Fighter 1: " + std::to_string(fighter1.lives), olc::BLACK);
		DrawString(1090, 10, "Fighter 2: " + std::to_string(fighter2.lives), olc::BLACK);
		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};