#pragma once
#ifndef DRAW_H
#define DRAW_H
#include "general.h"
#include "Image.h"
#include "Point.h"
#include "Rect.h"

namespace MNDT {

	void DrawLine8bit(Image& image, const Point& p1, const Point& p2, C_UCHAR& color = 255);

	void DrawPoint8bit(Image& image, const Point& point, C_UCHAR& color = 255);

	void DrawRect8bit(Image& image, const Rect& rect, C_UCHAR& color = 255);

	void DrawRect24bit(Image& image, const Rect& rect, Pixel& color);
}

#endif // !DRAW_H