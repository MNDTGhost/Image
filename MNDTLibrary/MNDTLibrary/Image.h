#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include "general.h"

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
	Image(UCHAE* src
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 type);

	~Image();

	UINT32 Width() const;

	UINT32 Height() const;

	UCHAE** image;
private:
	MNDT::ImageType _type;
	UINT32 _width;
	UINT32 _height;
};

#endif // !IMAGE_H


