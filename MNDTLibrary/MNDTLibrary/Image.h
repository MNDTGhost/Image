#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include "general.h"

class Image
{
public:
	Image(UCHAE* src, C_UINT32 width, C_UINT32 height);

	~Image();

	UINT32 Width() const;

	UINT32 Height() const;


	UCHAE** image;
private:
	UINT32 _width;
	UINT32 _height;
};

#endif // !IMAGE_H


