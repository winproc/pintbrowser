#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class PintHWResourceManager {
private:
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;

public:
	HWND hTargetWindow;
	HRESULT LoadResources();
	HRESULT InitFactory();

	HRESULT HWDraw();
	void ResizeTarget();

	void DiscardResources();
	void DestroyFactory();
};