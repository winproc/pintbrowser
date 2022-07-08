#pragma once

class PintRGB {
public:

	unsigned short r;
	unsigned short g;
	unsigned short b;
};

class Frame {
public:

	bool Rounded = false;
	bool Visible = true;
	bool Highlight = true;

	PintRGB BackgroundColor;
	D2D1_RECT_F Rect;

	void Create(D2D1_RECT_F strct, PintRGB col);
	bool Intersects(D2D1_RECT_F rc);
};

