#include "Rect.h"

void Rect::X(C_UINT32 x)
{
	_x = x;
}

UINT32 Rect::X() const
{
	return _x;
}

void Rect::Y(C_UINT32 y)
{
	_y = y;
}

UINT32 Rect::Y() const 
{
	return _y;
}

void Rect::Width(C_UINT32 width)
{
	_width = width;
}

UINT32 Rect::Width() const
{
	return _width;
}


void Rect::Height(C_UINT32 height)
{
	_height = height;
}

UINT32 Rect::Height() const
{
	return _height;
}

UINT32 Rect::EndX() const
{
	return _x + _width;
}

UINT32 Rect::EndY() const
{
	return _y + _height;
}