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
			this->OnResourceLoaded();
		}
	}
	return hres;
}

void PintHWResourceManager::AddDrawResource(D2D1_RECT_F inst, ID2D1SolidColorBrush* ptrBrush) {
	DrawResource dr;
	dr.rInst = inst;
	dr.pBrush = ptrBrush;

	this->lDrawList.push_back(dr);
}

ID2D1SolidColorBrush* PintHWResourceManager::AddBrushResource(D2D1_COLOR_F col) {
	ID2D1SolidColorBrush* brs;

	this->pRenderTarget->CreateSolidColorBrush(col, &brs);
	this->lpBrushResources.push_back(brs);

	return brs;
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

	for (DrawResource res : this->lDrawList) {
		
		this->pRenderTarget->FillRectangle(res.rInst, res.pBrush);
	}
	
	return this->pRenderTarget->EndDraw();
}

void PintHWResourceManager::DiscardResources() {
	for (int i = 0; i < lpBrushResources.size(); i++) {
		SafeRelease(&lpBrushResources[i]);
	}
	lpBrushResources.clear();
	SafeRelease(&this->pRenderTarget);
}

void PintHWResourceManager::DestroyFactory() {
	SafeRelease(&this->pFactory);
}