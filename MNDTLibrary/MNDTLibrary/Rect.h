#pragma once
#ifndef RECT_H
#define RECT_H
#include "general.h"
#include "Image.h"

class Rect {
public:
	Rect() : _x(0), _y(0), _width(0), _height(0) {};

	Rect(C_INT32 x, C_INT32 y, C_INT32 width, C_INT32 height) :_x(x), _y(y), _width(width), _height(height) {  };

	void X(C_INT32 x);
	int32_t X() const;

	void Y(C_INT32 y);
	int32_t Y() const;

	void Width(C_INT32 width);
	int32_t Width() const;

	void Height(C_INT32 height);
	int32_t Height() const;

	int32_t EndX() const;
	int32_t EndY() const;

	int32_t Area() const;

	friend Rect operator|(const Rect& rect1, const Rect& rect2);
	friend Rect operator&(const Rect& rect1, const Rect& rect2);
private:
	int32_t _x;
	int32_t _y;
	int32_t _width;
	int32_t _height;
};
#endif // !RECT_H