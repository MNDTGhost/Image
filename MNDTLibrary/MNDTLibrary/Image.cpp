#include "Image.h"

Image::Image(UCHAR* src
	, C_UINT32 width, C_UINT32 height
	, MNDT::ImageType type)
{
	_width = width;
	_height = height;
	_type = type;

	data = src;
	image = new UCHAR*[height];

	for (UINT32 index = 0; index < height; index++)
	{
		*(image + index) = (src + width * index * _type);
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

void Image::SetPixel(C_UINT32 row, C_UINT32 col, Pixel pix)
{
	switch (_type)
	{
	case MNDT::ImageType::GRAY_8BIT:
		image[row][col] = pix.B;
		break;
	case MNDT::ImageType::BGR_24BIT:
		C_UINT32 fixCol = col * 3;

		image[row][fixCol] = pix.B;
		image[row][fixCol + 1] = pix.G;
		image[row][fixCol + 2] = pix.R;
		break;
	}
}

Pixel Image::GetPixel(C_UINT32 row, C_UINT32 col) const
{
	Pixel pix;

	switch (_type)
	{
	case MNDT::ImageType::GRAY_8BIT:
		pix.B = image[row][col];
		pix.G = image[row][col];
		pix.R = image[row][col];
		break;
	case MNDT::ImageType::BGR_24BIT:
		C_UINT32 fixCol = col * 3;

		pix.B = image[row][fixCol];
		pix.G = image[row][fixCol + 1];
		pix.R = image[row][fixCol + 2];
		break;
	}

	return pix;
}