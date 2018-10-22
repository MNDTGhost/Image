#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#include "general.h"
#include "Image.h"
#include "draw.h"

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
		width		= Image's width
		height		= Image's height
		type		= change type
	*/
	void ChangeColor(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 type);

	/*
		AdjustmentHSV Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image's width
		height		= Image's height
		H		= H's %
		S		= S's %
		V		= V's %
	*/
	void AdjustmentHSV(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 H, C_INT32 S, C_INT32 V);

	/*
		AdjustmentYCbCr Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image's width
		height		= Image's height
		Y		= Y's %
		Cb		= Cb's %
		Cr		= Cr's %
	*/
	void AdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 Y, C_INT32 Cb, C_INT32 Cr);

	/*
		ImagePadding8bit Parameter:
		src		= source of image
		pur		= purpose of image
		width		= Image's width
		height		= Image's height
		pad		= padding size
	*/
	void ImagePadding8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 pad);

	/*
		Blur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		size		= blur block
	*/
	void Blur8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size);

	/*
		BlurGauss8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		size		= gauss temp size
		sigma		= gauss temp sigma
	*/
	void BlurGauss8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size, C_FLOAT sigma);

	/*
		MedianBlur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		size		= blur block
	*/
	void MedianBlur8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 size);

	/*
		MedianBlur8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
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
		width		= Image's width
		height		= Image's height
	*/
	void Histogram8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		SetHistogram8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		minRange	= min pixel
		maxRange	= max pixel
		bin			= histogran split size
	*/
	void SetHistogram8bit(C_UCHAE* src, int32_t* histogram
		, C_UINT32 width, C_UINT32 height);

	void SetHistogram8bit(C_UCHAE* src, int32_t* histogram
		, C_UINT32 width, C_UINT32 height
		, C_UCHAE minRange, C_UCHAE maxRange
		, C_UCHAE bin);

	/*
		SetNormalizedHistogram8bit Parameter:
		histogram	= histogram data
		size		= histogram size
		base		= max pixel
	*/
	void SetNormalizedHistogram8bit(int32_t* histogram
		, C_UINT32 size
		, C_UCHAE base);

	/*
		HistogramEqualization8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
	*/
	void HistogramEqualization8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		CompareHistogram Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
	*/
	double CompareHistogram(C_UCHAE* src, C_UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	/*
		Channel Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		channel		= color channel
	*/
	void Channel(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 channel);

	/*
		BackProjection Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
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
		width		= Image's width
		height		= Image's height
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
		Threshold8bit Parameter:
		src			= source of image
		pur			= purpose of image
		width		= Image's width
		height		= Image's height
		thresh		= threshold
	*/
	void Threshold8bit(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 thresh);
private:
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

	void Gaussian2DTemp(float** const temp, C_INT32 size, C_FLOAT sigma);

	void BilateralSpaceTemp(float** const temp, C_INT32 size, C_FLOAT sigma);

	void BilateralColorTemp(float* const temp, C_FLOAT sigma);

};


#endif // !LIBRARY_H