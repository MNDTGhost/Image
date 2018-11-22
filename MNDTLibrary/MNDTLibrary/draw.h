#pragma once
#ifndef DRAW_H
#define DRAW_H
#include "general.h"
#include "Image.h"
#include "Point.h"
#include "Rect.h"

namespace MNDT {

	extern void DrawLine8bit(const Image& image, const Point& p1, const Point& p2, C_UCHAE& color = 255);

	extern void DrawPoint8bit(const Image& image, const Point& point, C_UCHAE& color = 255);

	extern void DrawRect8bit(const Image& image, const Rect& rect, C_UCHAE& color = 255);

	extern void DrawRect24bit(const Image& image, const Rect& rect, Pixel& color);
}

#endif // !DRAW_H