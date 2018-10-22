#pragma once
#ifndef POINT_H
#define POINT_H
#include "general.h"
#include "Image.h"

class Point {
public:
	Point(C_UINT32 x, C_UINT32 y) :_x(x), _y(y) {};

	void X(C_UINT32 x);
	UINT32 X() const;

	void Y(C_UINT32 y);
	UINT32 Y() const;
private:
	UINT32 _x;
	UINT32 _y;
};
#endif // !POINT_H