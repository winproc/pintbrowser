#pragma once

#include <vector>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class DrawResource {
public:
	D2D1_RECT_F rInst;
	ID2D1SolidColorBrush* pBrush;
};

class PintHWResourceManager {
private:
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;

	std::vector<DrawResource> lDrawList;
	std::vector<ID2D1SolidColorBrush*> lpBrushResources;

public:
	HWND hTargetWindow;
	HRESULT LoadResources();
	HRESULT InitFactory();

	void OnResourceLoaded();

	HRESULT HWDraw();
	void ResizeTarget(); // unused

	void AddDrawResource(D2D1_RECT_F inst, ID2D1SolidColorBrush* pBrush);
	ID2D1SolidColorBrush* AddBrushResource(D2D1_COLOR_F col);

	void DiscardResources();
	void DestroyFactory();
};