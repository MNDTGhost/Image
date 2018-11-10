#pragma once
#ifndef RECT_H
#define RECT_H
#include "general.h"
#include "Image.h"

class Rect {
public:
	Rect() : _x(0), _y(0), _width(0), _height(0) {};

	Rect(C_UINT32 x, C_UINT32 y, C_UINT32 width, C_UINT32 height) :_x(x), _y(y), _width(width), _height(height) {  };

	void X(C_UINT32 x);
	UINT32 X() const;

	void Y(C_UINT32 y);
	UINT32 Y() const;

	void Width(C_UINT32 width);
	UINT32 Width() const;

	void Height(C_UINT32 height);
	UINT32 Height() const;

	UINT32 EndX() const;
	UINT32 EndY() const;

	UINT32 Area() const;

	friend Rect operator|(const Rect& rect1, const Rect& rect2);
private:
	UINT32 _x;
	UINT32 _y;
	UINT32 _width;
	UINT32 _height;
};
#endif // !RECT_H