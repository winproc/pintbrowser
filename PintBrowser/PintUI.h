#pragma once

#include "PintD2D.h"

class Frame {
public:
	
	int Id = 0;
	bool Rounded = false;
	bool Visible = true;
	bool Highlight = true;

	DrawResource *pRes;
	D2D1_COLOR_F BackgroundColor;
	D2D1_RECT_F Rect;
	
	void Create(D2D1_RECT_F strct, D2D1_COLOR_F col, std::vector<Frame>* lTarget);
	bool Intersects(D2D1_RECT_F rc);
	bool IntersectsPoint(D2D1_POINT_2F pCu);
	void OnMouseMove(bool Hovered);
};


