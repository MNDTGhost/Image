#pragma once
#ifndef DRAW_H
#define DRAW_H
#include "general.h"
#include "Image.h"
#include "Point.h"
#include "Rect.h"

namespace MNDT {
	inline void DrawLine8bit(const Image& image, const Point& p1, const Point& p2, C_UCHAE& color)
	{
		assert(image.Width() > p1.X() && image.Width() > p2.X());
		assert(image.Height() > p1.Y() && image.Height() > p2.Y());

		C_UINT32 diffX = abs(static_cast<int32_t>(p1.X()) - static_cast<int32_t>(p2.X()));
		C_UINT32 diffY = abs(static_cast<int32_t>(p1.Y()) - static_cast<int32_t>(p2.Y()));
		C_UINT32 base = diffX > diffY ? diffX : diffY;

		C_FLOAT baseX = static_cast<float>(diffX) / static_cast<float>(base);
		C_FLOAT baseY = static_cast<float>(diffY) / static_cast<float>(base);

		float x = static_cast<float>(p1.X());
		float y = static_cast<float>(p1.Y());

		for (UINT32 index = 0; index < base; index++)
		{
			image.image[static_cast<UINT32>(y)][static_cast<UINT32>(x)] = color;
			x += baseX;
			y += baseY;
		}
	}

	inline void DrawLine8bit(const Image& image, const Point& p1, const Point& p2)
	{
		DrawLine8bit(image, p1, p2, 255);
	}

	inline void DrawRect8bit(const Image& image, const Rect& rect, C_UCHAE& color)
	{
		C_UINT32 endX = rect.EndX();
		C_UINT32 endY = rect.EndY();

		for (UINT32 x = rect.X(); x < endX; x++)
		{
			image.image[rect.Y()][x] = color;
			image.image[endY][x] = color;
		}

		for (UINT32 y = rect.Y(); y < endY; y++)
		{
			image.image[y][rect.X()] = color;
			image.image[y][endX] = color;
		}
	}

	inline void DrawRect8bit(const Image& image, const Rect& rect)
	{
		DrawRect8bit(image, rect, 255);
	}
}

#endif // !DRAW_H