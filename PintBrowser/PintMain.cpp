#include <iostream>

#include "PintWinAPI.h"
#include "PintUI.h"
#include "PintD2D.h"
#include "App.h"

constexpr short HOME_BT = 1;

PintHWResourceManager DisplayManager;
std::vector<Frame> lUIList;

LRESULT CALLBACK callbackProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;

	switch (uMsg) {

	case WM_CREATE:
		if (FAILED(DisplayManager.InitFactory())) {
			return -1;
		}
		return 0;
	case WM_DESTROY:
		
		DisplayManager.DiscardResources();
		DisplayManager.DestroyFactory();
		PostQuitMessage(0);

		return 0;

	case WM_PAINT:
	
		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		
		if (SUCCEEDED(DisplayManager.LoadResources())) {
			HRESULT hr = DisplayManager.HWDraw();
			if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
				DisplayManager.DiscardResources();
			}
		}

		EndPaint(hwnd, &ps);
		
		return 0;
	case WM_MOUSEMOVE:
		short xp = GET_X_LPARAM(lParam);
		short yp = GET_Y_LPARAM(lParam);

		for (int i = 0; i < lUIList.size(); i++) {
			D2D1_POINT_2F mousePt;
			mousePt.x = xp;
			mousePt.y = yp;

			if (lUIList[i].IntersectsPoint(mousePt)) {
				lUIList[i].OnMouseMove(true);
			}
			else {
				lUIList[i].OnMouseMove(false);
			}
			InvalidateRect(hwnd, NULL, TRUE);
		}


	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// called when d2d resources are loaded
void PintHWResourceManager::OnResourceLoaded() {

	// load hover brush at 0th index (grey)
	DisplayManager.AddBrushResource(D2D1::ColorF((UINT32)0x404040));

	for (int i = 0; i < lUIList.size(); i++) {

		Frame frame = lUIList[i];
		ID2D1SolidColorBrush* ColorRes = this->AddBrushResource(frame.BackgroundColor);
		int index = this->AddDrawResource(frame.Rect, ColorRes);
		lUIList[i].pRes = &this->lDrawList.at(index);
		if (lUIList[i].Rounded) {
			lDrawList[index].Rounded = true;
		}
		
	}

	OutputDebugStringA("Resources loaded...");
	DisplayManager.ResourcesLoaded = true;

}

// called for every frame when mouse moves
void Frame::OnMouseMove(bool Hovered) {
	if (DisplayManager.ResourcesLoaded != true) {
		return;
	}

	if (Hovered) {
		this->pRes->pBrush = DisplayManager.GetBrush(0);
	}
	else {
		switch (this->Id) {
		case HOME_BT:
			this->pRes->pBrush = DisplayManager.GetBrush(2);
			break;
		}
		
	}
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow) {

	Application main;

	bool bInit = main.InitResources(hPrevInstance);
	if (!bInit) {
		std::cout << "Resource creation failure.\n";
		return 1;
	}

	main.m_fCallback = callbackProc;

	bool bOpen = main.Open(nCmdShow);


	if (bOpen) {

		// ui generation
		Frame bar;
		bar.Create(D2D1::RectF(0.0f, 0.0f, 1200.0f, 30.0f), D2D1::ColorF((UINT32)0x1f1f1f), &lUIList);

		Frame fHomeButton;
		fHomeButton.Id = HOME_BT;
		fHomeButton.Rounded = true;
		fHomeButton.Create(D2D1::RectF(20.0f, 5.0f, 90.0f, 25.0f), D2D1::ColorF((UINT32)0xffffff), &lUIList);

		// setup
		DisplayManager.hTargetWindow = main.m_hWindow;

		main.KeepAlive();
	}
	return 0;
};
