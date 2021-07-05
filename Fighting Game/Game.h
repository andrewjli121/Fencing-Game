#define OLC_PGE_APPLICATION 0
#pragma once
#include "olcPixelGameEngine.h"
#include <iostream>

class Game : public olc::PixelGameEngine
{
private:
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

	bool OnUserCreate() override {

		fOffsetX = -ScreenWidth() / 2;
		fOffsetY = -ScreenHeight() / 2;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {

		float fMouseX = (float)GetMouseX();
		float fMouseY = (float)GetMouseY();

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

		//horizontal lines
		for (float y = 0.0; y <= 10.0f; y++) {

			float sx = 0.0f, sy = y;
			float ex = 10.0f, ey = y;

			int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

			WorldToScreen(sx, sy, pixel_sx, pixel_sy);
			WorldToScreen(ex, ey, pixel_ex, pixel_ey);

			DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
		}

		//vertical lines
		for (float x = 0.0; x <= 10.0f; x++) {

			float sx = x, sy = 0.0f;
			float ex = x, ey = 10.0f;

			int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

			WorldToScreen(sx, sy, pixel_sx, pixel_sy);
			WorldToScreen(ex, ey, pixel_ex, pixel_ey);

			DrawLine(pixel_sx, pixel_sy, pixel_ex, pixel_ey, olc::WHITE);
		}
		return true;
	}

	void run() {
		if (Construct(300, 200, 6, 6)) {
			Start();
		}
	}
};