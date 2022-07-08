#include <iostream>

#include "PintWinAPI.h"
#include "PintD2D.h"
#include "PintUI.h"
#include "App.h"

PintHWResourceManager DisplayManager;

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
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void PintHWResourceManager::OnResourceLoaded() {
	OutputDebugStringA("test");
	ID2D1SolidColorBrush* MenuColor = this->AddBrushResource(D2D1::ColorF(0.0, 0.0, 1.0));
	this->AddDrawResource(D2D1::RectF(3.0f, 3.0f, 30.0f, 30.0f), MenuColor);

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
		
		DisplayManager.hTargetWindow = main.m_hWindow;

		main.KeepAlive();
	}
	return 0;
};
