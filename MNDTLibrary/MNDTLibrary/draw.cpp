#include "draw.h"
namespace MNDT {

	void DrawLine8bit(Image& image, const Point& p1, const Point& p2, C_UCHAR& color)
	{
		assert(image.Width() > p1.X() && image.Width() > p2.X());
		assert(image.Height() > p1.Y() && image.Height() > p2.Y());

		C_UINT32 absDiffX = abs(static_cast<int32_t>(p1.X()) - static_cast<int32_t>(p2.X()));
		C_UINT32 absDiffY = abs(static_cast<int32_t>(p1.Y()) - static_cast<int32_t>(p2.Y()));
		C_UINT32 base = absDiffX > absDiffY ? absDiffX : absDiffY;
		C_INT32 diffX = static_cast<int32_t>(p1.X()) - static_cast<int32_t>(p2.X());
		C_INT32 diffY = static_cast<int32_t>(p1.Y()) - static_cast<int32_t>(p2.Y());
		C_FLOAT baseX = -static_cast<float>(diffX) / static_cast<float>(base);
		C_FLOAT baseY = -static_cast<float>(diffY) / static_cast<float>(base);

		float x = static_cast<float>(p1.X());
		float y = static_cast<float>(p1.Y());

		for (UINT32 index = 0; index < base; index++)
		{
			image.image[static_cast<UINT32>(y)][static_cast<UINT32>(x)] = color;
			x += baseX;
			y += baseY;
		}
	}

	void DrawPoint8bit(Image& image, const Point& point, C_UCHAR& color)
	{
		assert(image.Width() > point.X() && image.Height() > point.Y());

		image.image[point.Y()][point.X()] = color;
	}

	void DrawRect8bit(Image& image, const Rect& rect, C_UCHAR& color)
	{
		C_UINT32 width = rect.EndX() + 1;
		C_UINT32 height = rect.EndY() + 1;

		for (UINT32 x = rect.X(); x < width; x++)
		{
			image.image[rect.Y()][x] = color;
			image.image[height - 1][x] = color;
		}

		for (UINT32 y = rect.Y(); y < height; y++)
		{
			image.image[y][rect.X()] = color;
			image.image[y][width - 1] = color;
		}
	}

	void DrawRect24bit(Image& image, const Rect& rect, Pixel& color)
	{
		C_INT32 width = rect.EndX() + 1;
		C_INT32 height = rect.EndY() + 1;

		for (int32_t x = rect.X(); x < width; x++)
		{
			if (rect.Y() < 0)
			{
				int i = 0;
			}
			image.SetPixel(rect.Y(), x, color);
			image.SetPixel(height - 1, x, color);
		}

		for (int32_t y = rect.Y(); y < height; y++)
		{
			if (y < 0)
			{
				int i = 0;
			}
			image.SetPixel(y, rect.X(), color);
			image.SetPixel(y, height - 1, color);
		}
	}
}