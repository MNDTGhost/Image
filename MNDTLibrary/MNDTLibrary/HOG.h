#pragma once
#ifndef HOG_H
#define HOG_H
#include "Library.h"

class HOG
{
public:
	~HOG();

	HOG(C_UINT32 cellX = 8, C_UINT32 cellY = 8, C_UINT32 blockX = 2, C_UINT32 blockY = 2) :
		_cellX(cellX), _cellY(cellY), _blockX(blockX), _blockY(blockY) {};

	inline C_UINT32 CellHisTotalSize(C_UINT32& width, C_UINT32& height) const;

	inline C_UINT32 BlockHisTotalSize(C_UINT32& width, C_UINT32& height) const;

	void GradienView(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height);

	void CellHistogram(C_UCHAR* src, C_UINT32 width, C_UINT32 height
		, float* histogram);

	void BlockHistogram(C_UCHAR* src, C_UINT32 width, C_UINT32 height
		, float* histogram);

	void HOGCellView(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height);

	void HOGBlockView(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height);

	void HOGDrawCell(UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, float* cellHistogram);
private:

	inline C_UINT32 FixWidth(C_UINT32& width) const;

	inline C_UINT32 FixHeight(C_UINT32& height) const;

	inline C_UINT32 CellXSize(C_UINT32& width) const;

	inline C_UINT32 CellYSize(C_UINT32& height) const;

	inline C_UINT32 BlockXSize(C_UINT32& cellXSize) const;

	inline C_UINT32 BlockYSize(C_UINT32& cellYSize) const;

	inline C_UINT32 BlockHisSize() const;

	void ReSize(C_UCHAR* src, UCHAR** resizeData
		, C_UINT32 width, C_UINT32 height);

	void Gradient(C_UCHAR* src
		, C_UINT32 width, C_UINT32 height
		, double* amplitudes, double* angles);

	void CalcCellHistogram(C_DOUBLE* angles, C_UINT32 width
		, float* histogram
		, C_UINT32 sWidth, C_UINT32 sHeight
		, C_UINT32 eWidth, C_UINT32 eHeight);

	void CalcBlockHistogram(C_FLOAT* cellHistogram, C_UINT32 cellXSize
		, float* histogram
		, C_UINT32 sCellX, C_UINT32 sCellY
		, C_UINT32 eCellX, C_UINT32 eCellY);

	void HistogramNorm(float* histogram
		, C_UINT32 hisTotalSize, C_UINT32 hisSIze
		, C_UINT32 base);

	void HistogramNorm2(float* histogram
		, C_UINT32 hisTotalSize, C_UINT32 hisSIze);

	void HOGViewSum(C_FLOAT* blockHistogram, C_UINT32 cellXSize
		, float* cellHistogram
		, UINT32* cellHisCount
		, C_UINT32 sCellX, C_UINT32 sCellY
		, C_UINT32 eCellX, C_UINT32 eCellY);

	void HOGViewAvg(float* cellHistogram, C_UINT32* cellHisCount
		, C_UINT32 cellTotalSize);

	C_UINT32 _bin = 9;
	C_UINT32 _cellX = 8;
	C_UINT32 _cellY = 8;
	C_UINT32 _blockX = 2;
	C_UINT32 _blockY = 2;
};

#endif // !HOG_H
