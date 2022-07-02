#include <iostream>

#include "PintWinAPI.h"
#include "PintD2D.h"

#include "App.h"

LRESULT CALLBACK callbackProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
		main.KeepAlive();
	}
	return 0;
};
