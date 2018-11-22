#include "Rect.h"

void Rect::X(C_INT32 x)
{
	_x = x;
}

int32_t Rect::X() const
{
	return _x;
}

void Rect::Y(C_INT32 y)
{
	_y = y;
}

int32_t Rect::Y() const
{
	return _y;
}

void Rect::Width(C_INT32 width)
{
	_width = width;
}

int32_t Rect::Width() const
{
	return _width;
}


void Rect::Height(C_INT32 height)
{
	_height = height;
}

int32_t Rect::Height() const
{
	return _height;
}

int32_t Rect::EndX() const
{
	if (_width == 0)
	{
		return -1;
	}

	return _x + _width - 1;
}

int32_t Rect::EndY() const
{
	if (_height == 0)
	{
		return -1;

	}
	return _y + _height - 1;
}

int32_t Rect::Area() const
{
	return _width * _height;
}

Rect operator|(const Rect& rect1, const Rect& rect2)
{
	C_INT32 minX = std::min(rect1.X(), rect2.X());
	C_INT32 minY = std::min(rect1.Y(), rect2.Y());
	C_INT32 maxX = std::max(rect1.EndX(), rect2.EndX());
	C_INT32 maxY = std::max(rect1.EndY(), rect2.EndY());

	return Rect(minX, minY, maxX - minX + 1, maxY - minY + 1);
}

Rect operator&(const Rect& rect1, const Rect& rect2)
{
	int32_t x[4] = { rect1.X(), rect1.EndX(), rect2.X(), rect2.EndX() };
	int32_t y[4] = { rect1.Y(), rect1.EndY(), rect2.Y(), rect2.EndY() };

	std::sort(x, x + 3);
	std::sort(y, y + 3);

	if (rect1.X() <= x[1] && rect1.EndX() >= x[2]
		&& rect1.Y() <= y[1] && rect1.EndY() >= y[2]
		&& rect2.X() <= x[1] && rect2.EndX() >= x[2]
		&& rect2.Y() <= y[1] && rect2.EndY() >= y[2])
	{
		return Rect(x[1], y[1], x[2] - x[1] + 1, y[2] - y[1] + 1);
	}

	return Rect(0, 0, 0, 0);
}