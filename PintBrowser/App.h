#pragma once

class Application {

private:
	HINSTANCE m_hAppInstance;
public:
	HWND m_hWindow;
	WNDPROC m_fCallback;
	
	bool Open(int nShowCode);
	bool InitResources(HINSTANCE hAppInstance);
	void KeepAlive();

	
};