#include "PintD2D.h"
#include "PintUI.h"

bool Frame::Intersects(D2D1_RECT_F rc) {
	D2D1_RECT_F rLrc = this->Rect;
	if (rLrc.left < rc.right && rLrc.right > rc.left && rLrc.top < rc.bottom && rLrc.bottom < rc.top) {
		return true;
	}
	return false;
}

void Frame::Create(D2D1_RECT_F strct, PintRGB col) {
	this->Rect = strct;
	this->BackgroundColor = col;
}