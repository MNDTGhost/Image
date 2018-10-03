#pragma once
#ifndef LIBRARY_H
#define LIBRARY_H
#include "general.h"

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
		Y		= Y's %
		Cb		= Cb's %
		Cr		= Cr's %
	*/
	void AdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 Y, C_INT32 Cb, C_INT32 Cr);
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
};


#endif // !LIBRARY_H