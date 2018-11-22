#pragma once
#ifndef LBP_H
#define LBP_H
#include "Library.h"
#include <bitset>
class LBP
{
public:
	LBP();
	~LBP();

	void OriginalLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height);

	void CircularLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 radius = 1, C_UINT32 bin = 8);

	void InvariantLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 radius = 1, C_UINT32 bin = 8);

	void EquivalentLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 radius = 1, C_UINT32 bin = 8);

	void MultiScaleBlockLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 scale = 9);

	void SEMultiScaleBlockLBP(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_INT32 scale = 9);

	void LBPHistogram(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 gridX, C_UINT32 gridY
		, C_UINT32 bin = 256);
private:
	void EquivalentTable(UCHAE* table);
};


#endif