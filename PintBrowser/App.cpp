
#include "PintWinAPI.h"
#include "App.h"

bool Application::InitResources(HINSTANCE hAppInstance) {
	this->m_hAppInstance = hAppInstance;
	return true;
}

// entry function
bool Application::Open(int nShowCode) {

	WNDCLASS wndMain = {};

	wndMain.lpfnWndProc = this->m_fCallback;
	wndMain.hInstance = this->m_hAppInstance;
	wndMain.lpszClassName = L"PintBrowsing";

	RegisterClass(&wndMain);

	const DWORD styleFlags = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	this->m_hWindow = CreateWindowExW(0, wndMain.lpszClassName, L"Pint Browser", styleFlags, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, m_hAppInstance, NULL);
	if (!m_hWindow) {
		return false;
	}

	ShowWindow(m_hWindow, nShowCode);

	return true;

};

// message loop
void Application::KeepAlive() {
	MSG msg = {};
	while (GetMessageA(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}