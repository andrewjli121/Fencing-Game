#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include "StateController.h"
#include "Camera.h"
#include "Fighter.h"
#include "Collision.h"

class Game : public olc::PixelGameEngine
{
private:

	StateController* stateController = nullptr;
	Fighter fighter1;
	Fighter fighter2;
	Camera camera;

	olc::Sprite* playerOnePtr = nullptr;
	olc::Sprite* playerTwoPtr = nullptr;
	olc::Decal* playerOneDecal = nullptr;
	olc::Decal* playerTwoDecal = nullptr;
	Collision test;

public:

	~Game() {
		delete playerOnePtr;
		delete playerOneDecal;
		delete playerTwoDecal;
	}

	bool OnUserCreate() override {

		//Sprite ptrs
		playerOnePtr = new olc::Sprite("Resources/fighter1.png");
		playerTwoPtr = new olc::Sprite("Resources/fighter1.png");
		playerOneDecal = new olc::Decal(playerOnePtr);
		playerTwoDecal = new olc::Decal(playerOnePtr);

		//State referencing/obj
		stateController = new StateController;
		stateController->Init();

		//Default offset
		camera.fOffsetX = -ScreenWidth() * 0.50;
		camera.fOffsetY = -ScreenHeight() * 0.55;
		fighter1.position.x = -playerOnePtr->width / 2;
		fighter1.position.y = -playerOnePtr->height / 2;
		fighter2.position.x = -playerTwoPtr->width / 2;
		fighter2.position.y = -playerTwoPtr->height / 2;

		Collision::makequad(test.quad);
		Collision::makequad(test.quad2);

		//std::fstream center{ "Hitboxes//center.txt" };
		//std::fstream head{ "Hitboxes//head.txt" };
		//Collision::getpoly(*fighter1.hitBoxes[0], center);
		//Collision::getpoly(*fighter1.hitBoxes[1], head);
		fighter1.linkFiles(fighter1.hitBoxes);
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

		Clear(olc::BLACK);

		//Move Player 1
		if (GetKey(olc::Key::LEFT).bHeld) {
			fighter1.position.x -= (1000 * fElapsedTime);
			stateController->TransitionTo("LEFT");
		}

		if (GetKey(olc::Key::RIGHT).bHeld) {
			fighter1.position.x += (1000 * fElapsedTime);
			stateController->TransitionTo("RIGHT");
		}

		//Move Player 2
		if (GetKey(olc::Key::D).bHeld) {
			fighter2.position.x += (1000 * fElapsedTime);
		}

		if (GetKey(olc::Key::A).bHeld) {
			fighter2.position.x -= (1000 * fElapsedTime);
		}

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

		//Transition State
		stateController->TransitionTo("IDLE");
		stateController->Update();

		//Draw Decals
		SetPixelMode(olc::Pixel::MASK);
		FillCircle(600, 540, 2, olc::YELLOW);
		FillCircle(camera.pixel_onex + (playerOnePtr->width / 2 * camera.fScaleX), camera.pixel_oney, 2, olc::RED);
		FillCircle(camera.pixel_twox + (playerTwoPtr->width / 2 * camera.fScaleX), camera.pixel_twoy, 2, olc::BLUE);
		DrawDecal(olc::vf2d(camera.pixel_onex, camera.pixel_oney), playerOneDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		DrawDecal(olc::vf2d(camera.pixel_twox, camera.pixel_twoy), playerTwoDecal, olc::vf2d(camera.fScaleX, camera.fScaleY));
		
		test.updatepoly(test.quad);

		test.updatepoly(test.quad2);

		for (auto *a : fighter1.hitBoxes) {
			Collision::updatepoly(*a);
		}

		test.quad2.pos.x = 170;
		test.quad.overlap = test.collision(test.quad, test.quad2);
		test.quad2.overlap = test.collision(test.quad, test.quad2);
		fighter1.hitBoxes[0]->angle += 2 * fElapsedTime;

		Collision::allCollision(fighter1.hitBoxes, fighter1.hitBoxes);

		Collision::drawpoly(test.quad);
		Collision::drawpoly(test.quad2);
		for (polygon *a : fighter1.hitBoxes) {
			Collision::drawpoly(*a);
		}



		test.quad.angle += 2 * fElapsedTime;

		return true;
	}

	void run() {
		if (Construct(1200, 600, 1, 1)) {
			Start();
		}
	}
};