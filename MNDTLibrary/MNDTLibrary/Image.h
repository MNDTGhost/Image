#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include "general.h"

struct Pixel {
	UCHAR B, G, R;
	Pixel(C_UCHAR& b, C_UCHAR g, C_UCHAR r) {
		B = b;
		G = g;
		R = r;
	}

	Pixel(C_UCHAR& gray) {
		Pixel(gray, gray, gray);
	}

	Pixel() {
		Pixel(0, 0, 0);
	}

};

class Image
{
public:
	/*
		Image Parameter:
		src			= source of image
		width		= Image width
		height		= Image height
		type		= Image type
	*/
	Image(UCHAR* src
		, C_UINT32 width, C_UINT32 height
		, MNDT::ImageType type);

	~Image();

	UINT32 Width() const;

	UINT32 Height() const;

	void SetPixel(C_UINT32 row, C_UINT32 col, Pixel pix);

	Pixel GetPixel(C_UINT32 row, C_UINT32 col) const;

	UCHAR** image;
	UCHAR* data;
private:
	MNDT::ImageType _type;
	UINT32 _width;
	UINT32 _height;
};

#endif // !IMAGE_H


