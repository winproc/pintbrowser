#pragma once

class Application {

private:
	HINSTANCE m_hAppInstance;
	
	HWND m_hWindow;

public:
	WNDPROC m_fCallback;
	bool Open(int nShowCode);
	bool InitResources(HINSTANCE hAppInstance);
	void KeepAlive();
};