#pragma once

class Camera {
private:

	float fStartPanX{ 0.0f };
	float fStartPanY{ 0.0f };

public:
	float fScaleX{ 1.0f };
	float fScaleY{ 1.0f };
	float fOffsetX{ 0 };
	float fOffsetY{ 0 };

	int pixel_onex, pixel_oney, pixel_twox, pixel_twoy;

	float fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom, fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom;

	void WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY);

	void ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY);

	void MousePressed(float fMouseX, float fMouseY);

	void MouseHeld(float fMouseX, float fMouseY);

	void ZoomSmall(int scroll);

	void ZoomBig(int scroll);

	void DynamicZoom(float fZeroX, float fZeroY, int zoom);

	void ChangeOffset(float FBZ, float FAZ, bool xy);
};

