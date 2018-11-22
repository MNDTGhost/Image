#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#include "general.h"
#include "Image.h"
#include "draw.h"
#include "GaussianElimination.h"

enum ColerType
{
	BGR2GRAY_8BIT,
	BGR2HSV,
	HSV2BGR,
	BGR2YCbCr,
	YCbCr2BGR,
};

class Library
{
public:
	Library();

	~Library();

	/*
		ChangeColor Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		type		= change type
	*/
	void ChangeColor(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 type);

	/*
		AdjustmentHSV Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image width
		height		= Image height
		H		= H %
		S		= S %
		V		= V %
	*/
	void AdjustmentHSV(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 H, C_INT32 S, C_INT32 V);

	/*
		AdjustmentYCbCr Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image width
		height		= Image height
		Y		= Y %
		Cb		= Cb %
		Cr		= Cr %
	*/
	void AdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 Y, C_INT32 Cb, C_INT32 Cr);

	/*
		ImagePadding8bit Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image width
		height		= Image height
		pad		= padding size
	*/
	void ImagePadding8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 pad);

	/*
		ImagePadding24bit Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image width
		height		= Image height
		pad		= padding size
	*/
	void ImagePadding24bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 pad);

	/*
		Blur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		size		= blur block
	*/
	void Blur8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size);

	/*
		BlurGauss8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		size		= gauss temp size
		sigma		= gauss temp sigma
	*/
	void BlurGauss8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size, C_FLOAT sigma);

	/*
		BlurGauss24bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		size		= gauss temp size
		sigma		= gauss temp sigma
	*/
	void BlurGauss24bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size, C_FLOAT sigma);

	/*
		MedianBlur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		size		= blur block
	*/
	void MedianBlur8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size);

	/*
		MedianBlur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		spaceSigma	= space sigma
		colorSigma	= space sigma
		size		= blur block
	*/

	void BilateralBlur8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT spaceSigma, C_FLOAT colorSigma
		, C_UINT32 size);

	/*
		Histogram8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	void Histogram8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		SetHistogram8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		minRange	= min pixel
		maxRange	= max pixel
		bin			= histogran split size
	*/
	void SetHistogram8bit(C_UCHAE* src, int32_t* histogram
		, C_UINT32 width, C_UINT32 height
		, C_UCHAE minRange, C_UCHAE maxRange
		, C_UCHAE bin);

	void SetHistogram8bit(C_UCHAE* src, int32_t* histogram
		, C_UINT32 width, C_UINT32 height);

	template <class T>
	void SetHistogram24bit(C_UCHAE* src, T* histogram
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 minRange, C_UINT32 maxRange
		, C_UINT32 bin);

	/*
		SetNormalizedHistogram8bit Parameter:
		histogram	= histogram data
		size		= histogram size
		base		= max pixel
	*/
	template <class T>
	void SetNormalizedHistogram8bit(T* histogram
		, C_UINT32 size
		, C_FLOAT base);

	void SetNormalizedHistogram8bit(float* histogram
		, C_UINT32 size
		, MNDT::Normalized type);

	void SetNormalizedHistogram24bit(float* histogram
		, C_UINT32 size);

	/*
		HistogramEqualization8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	void HistogramEqualization8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		CompareHistogram Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	double CompareHistogram(C_UCHAE* src, C_UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		Channel Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		channel		= color channel
	*/
	void Channel(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 channel);

	/*
		BackProjection Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		histogram	= histogram data
		minRange	= min pixel
		maxRange	= max pixel
		bin			= histogran split size
	*/
	void BackProjection(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32* histogram
		, C_UCHAE minRange, C_UCHAE maxRange
		, C_UCHAE bin);

	/*
		MeanShift Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		rectPoint	= original rect point
		time		= trans time
		threshold	= diff threshold
	*/
	void MeanShift(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32* rectPoint
		, C_UINT32 times
		, C_DOUBLE threshold);

	/*
		Rotate8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		type		= threshold
	*/
	void Rotate8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, MNDT::RotateType type);

	/*
		Resize Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		reWidth		= new width
		reHeight	= new height
		type		= resize type
	*/
	void Resize8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 reWidth, C_UINT32 reHeight
		, MNDT::ResizeType type);

	/*
		PyramidDown8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	void PyramidDown8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		PyramidUp8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	void PyramidUp8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		SetAffineTransform Parameter:
		affine		= point input and output
		baseX		= ouput x base(a.b.c)
		baseY		= ouput y base(a.b.c)
		row			= row size
		col			= col size
	*/
	void SetAffineTransform(float** affine
		, float* baseX, float* baseY
		, C_UINT32 row, C_UINT32 col);

	/*
		Affine8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		baseX		= ouput x base(a.b.c)
		baseY		= ouput y base(a.b.c)
	*/
	void Affine8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT* baseX, C_FLOAT* baseY);

	/*
		Sobel8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		dx			= x gradient switch
		dy			= y gradient switch
	*/
	void Sobel8bit(C_UCHAE* src, int32_t* pur
		, C_UINT32 width, C_UINT32 height
		, const bool dx, const bool dy);

	/*
		SobelEdgeView8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
	*/
	void SobelEdgeView8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		Sobel24bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		dx			= x gradient switch
		dy			= y gradient switch
	*/
	void Sobel24bit(C_UCHAE* src, int32_t* pur
		, C_UINT32 width, C_UINT32 height
		, const bool dx, const bool dy);

	/*
		SobelVisualization24bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		dx			= x gradient switch
		dy			= y gradient switch
	*/
	void SobelVisualization24bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, const bool dx, const bool dy);

	/*
		CartToPolar Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		magnitude	= Image magnitude
		angle		= Image angle
		type		= image type(8bit, 24bit....)
	*/
	void CartToPolar(C_INT32* Gx, C_INT32* Gy
		, C_UINT32 width, C_UINT32 height
		, float* magnitude, float* angle
		, MNDT::ImageType type);

	/*
		Gamma8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		gamma		= calculation parmas
	*/
	void Gamma8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_DOUBLE gamma);
	
	/*
		HoughLines Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		rho			= calculation sin and cos
		theta		= calculation split parmas
		threshold	= calculation output parmas
	*/
	void HoughLines(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT rho, C_FLOAT theta, C_UINT32 threshold);

	/*
		HoughCircles Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		minRadius	= min radius
		maxRadius	= max radius
		threshold	= calculation output parmas
	*/
	void HoughCircles(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT minRadius, C_FLOAT maxRadius, C_UINT32 threshold);

	/*
		Threshold8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image width
		height		= Image height
		thresh		= threshold
	*/
	void Threshold8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 thresh);
private:
	// tool start
	void Gaussian2DTemp(float** const temp, C_INT32 size, C_FLOAT sigma);

	void SetSobelKernels(int32_t* kernels
		, const bool dx, const bool dy);
	// tool end



	// change color start
	void BGR2Gray8Bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void BGR2HSV(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void SetBGR2HSV(double* const hsv
		, C_DOUBLE& B, C_DOUBLE& G, C_DOUBLE& R);

	void HSV2BGR(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void SetHSV2BGR(double* const bgr
		, C_DOUBLE& H, C_DOUBLE& S, C_DOUBLE& V);

	void BGR2YCbCr(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void SetBGR2YCbCr(int32_t* const ycbcr
		, C_INT32& B, C_INT32& G, C_INT32& R);

	void YCbCr2BGR(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void SetYCbCr2BGR(int32_t* const bgr
		, C_INT32& Y, C_INT32& Cb, C_INT32& Cr);
	// change color end



	// change size and postion start
	void BilateralSpaceTemp(float** const temp, C_INT32 size, C_FLOAT sigma);

	void BilateralColorTemp(float* const temp, C_FLOAT sigma);

	void RotateHorizontal8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void RotateVertical8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void NearestResize8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 reWidth, C_UINT32 reHeight);

	void LinearResize8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 reWidth, C_UINT32 reHeight);
	// change size and postion end



	// normalized start
	void L1NormalizedHistogram8bit(float* histogram
		, C_UINT32 size);

	void L2NormalizedHistogram8bit(float* histogram
		, C_UINT32 size);
	// normalized end



	// Hough start
	void DrawHoughPolar(UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32* count
		, C_FLOAT theta, C_UINT32 maxR);

	void HoughLineNeighboursUpdate(UINT32* count
		, C_UINT32 thetaSize, C_UINT32 maxR
		, C_UINT32 threshold);

	void HoughCirclesCount(C_UCHAE* src
		, C_UINT32 width, C_UINT32 height
		, UINT32* count
		, C_FLOAT minRadius, C_FLOAT maxRadius);

	void HoughCirclePointCount(UINT32* count
		, C_UINT32 width
		, const Point& p1, const Point& p2);

	void HoughCircleNeighboursUpdate(UINT32* count
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 threshold);
	// Hough end
};

template <class T>
void Library::SetHistogram24bit(C_UCHAE* src, T* histogram
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 minRange, C_UINT32 maxRange
	, C_UINT32 bin)
{
	assert(maxRange > minRange);

	C_UCHAE diffRange = maxRange - minRange;
	C_UCHAE interval = diffRange / bin;
	C_UINT32 size = width * height;
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::BGR_24BIT);

	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			Pixel pix = srcImage.GetPixel(row, col);

			histogram[(pix.B / interval) % bin]++;
			histogram[(pix.G / interval + bin) % bin]++;
			histogram[(pix.R / interval + bin + bin) % bin]++;
		}
	}
}

template <class T>
void Library::SetNormalizedHistogram8bit(T* histogram
	, C_UINT32 size
	, C_FLOAT base)
{
	T max = 0;

	for (UINT32 index = 0; index < size; index++)
	{
		max = max < histogram[index] ? histogram[index] : max;
	}


	float normalizedBase = static_cast<float>(base) / max;

	for (UINT32 index = 0; index < size; index++)
	{
		histogram[index] = static_cast<T>(histogram[index] * normalizedBase);
	}
}

#endif // !LIBRARY_H