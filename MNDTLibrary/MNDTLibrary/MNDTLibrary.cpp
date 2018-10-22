#ifdef MNDTLIBRARY_EXPORTS
#define MNDTLIBRARY_API __declspec(dllexport)
#include "Library.h"

extern "C" MNDTLIBRARY_API void mndtWrite(C_UCHAE* msg)
{
	MNDT::Write(msg);
}

extern "C" MNDTLIBRARY_API void mndtChangeColor(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 type)
{
	Library lib;
	lib.ChangeColor(src, pur
		, width, height
		, type);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentHSV(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 H, C_INT32 S, C_INT32 V)
{
	Library lib;
	lib.AdjustmentHSV(src, pur
		, width, height
		, H, S, V);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 Y, C_INT32 Cb, C_INT32 Cr)
{
	Library lib;
	lib.AdjustmentYCbCr(src, pur
		, width, height
		, Y, Cb, Cr);
}

extern "C" MNDTLIBRARY_API void mndtImagePadding8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 pad)
{
	Library lib;
	lib.ImagePadding8bit(src, pur
		, width, height
		, pad);
}

extern "C" MNDTLIBRARY_API void mndtBlur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	Library lib;
	lib.Blur8bit(src, pur
		, width, height
		, size);
}

extern "C" MNDTLIBRARY_API void mndtBlurGauss8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size, C_FLOAT sigma)
{
	Library lib;
	lib.BlurGauss8bit(src, pur
		, width, height
		, size, sigma);
}

extern "C" MNDTLIBRARY_API void mndtMedianBlur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	Library lib;
	lib.MedianBlur8bit(src, pur
		, width, height
		, size);
}

extern "C" MNDTLIBRARY_API void mndtBilateralBlur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT spaceSigma, C_FLOAT colorSigma
	, C_UINT32 size)
{
	Library lib;
	lib.BilateralBlur8bit(src, pur
		, width, height
		, spaceSigma, colorSigma
		, size);
}

extern "C" MNDTLIBRARY_API void mndtHistogram8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	Library lib;
	lib.Histogram8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtHistogramEqualization8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	Library lib;
	lib.HistogramEqualization8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API double mndtCompareHistogram(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	Library lib;
	return lib.CompareHistogram(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtChannel(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 channel)
{
	Library lib;
	lib.Channel(src, pur
		, width, height
		, channel);
}

extern "C" MNDTLIBRARY_API void mndtBackProjection(C_UCHAE* src, UCHAE* pur
	, C_UINT32 srcWidth, C_UINT32 srcHeight
	, C_UINT32* histogram
	, C_UCHAE minRange, C_UCHAE maxRange
	, C_UCHAE bin)
{
	Library lib;
	lib.BackProjection(src, pur
		, srcWidth, srcHeight
		, histogram
		, minRange, maxRange
		, bin);
}

extern "C" MNDTLIBRARY_API void mndtSetHistogram8bit(C_UCHAE* src, int32_t* histogram
	, C_UINT32 hisWidth, C_UINT32 hisHeight
	, C_UCHAE minRange, C_UCHAE maxRange
	, C_UCHAE bin)
{
	Library lib;
	lib.SetHistogram8bit(src, histogram
		, hisWidth, hisHeight
		, minRange, maxRange
		, bin);
}

extern "C" MNDTLIBRARY_API void mndtSetNormalizedHistogram8bit(int32_t* histogram
	, C_UINT32 bin
	, C_UCHAE maxRange)
{
	Library lib;
	lib.SetNormalizedHistogram8bit(histogram
		, bin
		, maxRange);
}

extern "C" MNDTLIBRARY_API void mndtThreshold8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 thresh)
{
	Library lib;
	lib.Threshold8bit(src, pur
		, width, height
		, thresh);
}

extern "C" MNDTLIBRARY_API void mndtMeanShift(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32* rectPoint
	, C_UINT32 times
	, C_DOUBLE threshold)
{
	Library lib;
	lib.MeanShift(src, pur
		, width, height
		, rectPoint
		, times
		, threshold);
}

#else
#define MNDTLIBRARY_API __declspec(dllimport)
#endif