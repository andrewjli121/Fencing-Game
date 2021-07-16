#pragma once
#include "olcPixelGameEngine.h"

class Camera {
private:

	float fStartPanX = 0.0f;
	float fStartPanY = 0.0f;
	
public:
	float fScaleX = 1.0f;
	float fScaleY = 1.0f;
	float fOffsetX = 0;
	float fOffsetY = 0;

	olc::vf2d position = { 0.0f, 0.0f };

	int pixel_onex, pixel_oney, pixel_twox, pixel_twoy;

	float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom;
	float fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;

	void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY);

	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY);

	void MousePressed(float fMouseX, float fMouseY, bool a);

	void MouseHeld(float fMouseX, float fMouseY, bool a);

	void Zoom(int scroll);

	void ChangeOffset(float FBZ, float FAZ);

	//void ChangePos(Camera &camera, float fElapsedTime);
};

