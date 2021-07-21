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

void Camera::ZoomSmall(int scroll) {
	if (scroll > 0) {
		fScaleX *= 1.001f;
		fScaleY *= 1.001f;
	}
	else if (scroll < 0) {
		fScaleX *= 0.999f;
		fScaleY *= 0.999f;
	}
}

void Camera::ZoomBig(int scroll) {
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

void Camera::DynamicZoom(float fZeroX, float fZeroY, int zoom) {
	ScreenToWorld(fZeroX, fZeroY, fMouseWorldX_BeforeZoom, fMouseWorldY_BeforeZoom);
	ZoomSmall(zoom);
	ScreenToWorld(fZeroX, fZeroY, fMouseWorldX_AfterZoom, fMouseWorldY_AfterZoom);
	ChangeOffset(fMouseWorldX_BeforeZoom, fMouseWorldX_AfterZoom, true);
	ChangeOffset(fMouseWorldY_BeforeZoom, fMouseWorldY_AfterZoom, false);
}