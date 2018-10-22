#include "Image.h"

Image::Image(UCHAE* src
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 type)
{
	_width = width;
	_height = height;
	_type = static_cast<MNDT::ImageType>(type);

	image = new UCHAE*[height];

	for (UINT32 index = 0; index < height; index++)
	{
		*(image + index) = (src + width * index);
	}
}

Image::~Image()
{
	delete[] image;
	image = nullptr;
}

UINT32 Image::Width() const 
{
	return _width;
}

UINT32 Image::Height() const 
{
	return _height;
}
