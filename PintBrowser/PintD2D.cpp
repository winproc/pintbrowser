#include "PintD2D.h"

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

HRESULT PintHWResourceManager::InitFactory() {
	return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->pFactory);
}

HRESULT PintHWResourceManager::LoadResources() {
	HRESULT hres = S_OK;
	if (pRenderTarget == NULL) {
		RECT rc;
		GetClientRect(this->hTargetWindow, &rc);

		D2D1_SIZE_U wSize = D2D1::SizeU(rc.right, rc.bottom);

		hres = this->pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(this->hTargetWindow, wSize), &this->pRenderTarget);
		if (SUCCEEDED(hres)) {

			const D2D1_COLOR_F grey = D2D1::ColorF(0.3f, 0.3f, 0.3f);
			hres = this->pRenderTarget->CreateSolidColorBrush(grey, &this->pBrush);

		}
	}
	return hres;
}

// not used
void PintHWResourceManager::ResizeTarget() {
	if (this->pRenderTarget != NULL) {
		RECT wRc;
		GetClientRect(this->hTargetWindow, &wRc);

		D2D1_SIZE_U winSize = D2D1::SizeU(wRc.right, wRc.bottom);

		this->pRenderTarget->Resize(winSize);
		InvalidateRect(this->hTargetWindow, NULL, FALSE);
	}
}

HRESULT PintHWResourceManager::HWDraw() {
	this->pRenderTarget->BeginDraw();

	this->pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	this->pRenderTarget->FillRectangle(D2D1::RectF(2.0f, 2.0f, 32.0f, 32.0f), this->pBrush);

	return this->pRenderTarget->EndDraw();
}

void PintHWResourceManager::DiscardResources() {
	SafeRelease(&this->pBrush);
	SafeRelease(&this->pRenderTarget);
}

void PintHWResourceManager::DestroyFactory() {
	SafeRelease(&this->pFactory);
}