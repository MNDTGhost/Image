#pragma once
#ifndef HOUGH_H
#define HOUGH_H
#include "general.h"
#include "Library.h"

namespace MNDT {
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
	void HoughLines(C_UCHAR* src, UCHAR* pur
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
	void HoughCircles(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT minRadius, C_FLOAT maxRadius, C_UINT32 threshold);


}

namespace MNDT {
	namespace Inner {
		// Hough Line start
		void DrawHoughPolar(UCHAR* pur
			, C_UINT32 width, C_UINT32 height
			, C_UINT32* count
			, C_FLOAT theta, C_UINT32 maxR);

		void HoughLineNeighboursUpdate(UINT32* count
			, C_UINT32 thetaSize, C_UINT32 maxR
			, C_UINT32 threshold);
		// Hough Line end


		// Hough Circle end
		void HoughCirclesCount(C_UCHAR* src
			, C_UINT32 width, C_UINT32 height
			, UINT32* count
			, C_FLOAT minRadius, C_FLOAT maxRadius);

		void HoughCirclePointCount(UINT32* count
			, C_UINT32 width
			, const Point& p1, const Point& p2);

		void HoughCircleNeighboursUpdate(UINT32* count
			, C_UINT32 width, C_UINT32 height
			, C_UINT32 threshold);
		// Hough Circle end
	}
}

#endif
