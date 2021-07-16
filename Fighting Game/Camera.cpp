#include "Camera.h"

void Camera::WorldToScreen(float fWorldX, float fWorldY, int& nScreenX, int& nScreenY) {
	nScreenX = (int)((fWorldX - fOffsetX) * fScaleX);
	nScreenY = (int)((fWorldY - fOffsetY) * fScaleY);
}

void Camera::ScreenToWorld(int nScreenX, int nScreenY, float& fWorldX, float& fWorldY) {
	fWorldX = ((float)(nScreenX) / fScaleX) + fOffsetX;
	fWorldY = ((float)(nScreenY) / fScaleY) + fOffsetY;
}

void Camera::MousePressed(float fMouseX, float fMouseY) {
	fStartPanX = fMouseX;
	fStartPanY = fMouseY;
}

void Camera::MouseHeld(float fMouseX, float fMouseY) {
	fOffsetX -= (fMouseX - fStartPanX) / fScaleX;
	fOffsetY -= (fMouseY - fStartPanY) / fScaleY;

	fStartPanX = fMouseX;
	fStartPanY = fMouseY;
}

void Camera::Zoom(int scroll) {
	if (scroll > 0) {
		fScaleX *= 1.05f;
		fScaleY *= 1.05f;
	}
	else if (scroll < 0) {
		fScaleX *= 0.95f;
		fScaleY *= 0.95f;
	}
}

void Camera::ChangeOffset(float FBZ, float FAZ, bool xy) {
	if (xy) {
		fOffsetX += (FBZ - FAZ);
	}
	else {
		fOffsetY += (FBZ - FAZ);
	}
}
