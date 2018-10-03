#include "Image.h"

Image::Image(UCHAE* src, C_UINT32 width, C_UINT32 height)
{
	_width = width;
	_height = height;
	image = new UCHAE*[_height];

	for (UINT32 index = 0; index < _height; index++)
	{
		*(image + index) = (src + _width * index);
	}
}

Image::~Image()
{
	MNDT::DeletePtr(&image);
}

UINT32 Image::Width() const 
{
	return _width;
}

UINT32 Image::Height() const 
{
	return _height;
}
