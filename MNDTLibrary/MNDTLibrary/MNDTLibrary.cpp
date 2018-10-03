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
	lib.ChangeColor(src, pur, width, height, type);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentHSV(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 H, C_INT32 S, C_INT32 V)
{
	Library lib;
	lib.AdjustmentHSV(src, pur, width, height, H, S, V);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 Y, C_INT32 Cb, C_INT32 Cr)
{
	Library lib;
	lib.AdjustmentYCbCr(src, pur, width, height, Y, Cb, Cr);
}

#else
#define MNDTLIBRARY_API __declspec(dllimport)
#endif