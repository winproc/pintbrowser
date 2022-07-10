#pragma once

#include <string>
#include <vector>

#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")

class DrawResource {
public:
	D2D1_RECT_F rInst{};
	bool Rounded = false;

	ID2D1SolidColorBrush* pBrush{};
	
	DrawResource() {};
	
	std::wstring Text = L"nl";
};

class PintHWResourceManager {
private:
	ID2D1Factory* pFactory;
	IDWriteFactory* pWFactory;
	ID2D1HwndRenderTarget* pRenderTarget;

	std::vector<DrawResource> lDrawList;
	std::vector<ID2D1SolidColorBrush*> lpBrushResources;

public:
	bool ResourcesLoaded = false;

	HWND hTargetWindow;
	HRESULT LoadResources();
	HRESULT InitFactory();

	void OnResourceLoaded();

	HRESULT HWDraw();
	void ResizeTarget(); // unused

	int AddDrawResource(D2D1_RECT_F inst, ID2D1SolidColorBrush* pBrush);
	ID2D1SolidColorBrush* AddBrushResource(D2D1_COLOR_F col);
	ID2D1SolidColorBrush* GetBrush(int index);

	void DiscardResources();
	void DestroyFactory();
};