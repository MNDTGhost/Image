#include "Point.h"

void Point::X(C_UINT32 x) {
	_x = x;
}

UINT32 Point::X() const {
	return _x;
}

void Point::Y(C_UINT32 y) {
	_y = y;
}

UINT32 Point::Y() const {
	return _y;
}