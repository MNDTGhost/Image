#include "HOG.h"

HOG::~HOG()
{
}

inline C_UINT32 HOG::FixWidth(C_UINT32& width) const
{
	return static_cast<UINT32>(ceil(static_cast<float>(width) / _cellX) * _cellX);
}

inline C_UINT32 HOG::FixHeight(C_UINT32& height) const
{
	return static_cast<UINT32>(ceil(static_cast<float>(height) / _cellY) * _cellY);
}

inline C_UINT32 HOG::CellXSize(C_UINT32& width) const
{
	return static_cast<UINT32>(ceil(static_cast<float>(width) / _cellX));
}

inline C_UINT32 HOG::CellYSize(C_UINT32& height) const
{
	return static_cast<UINT32>(ceil(static_cast<float>(height) / _cellY));
}

inline C_UINT32 HOG::BlockXSize(C_UINT32& cellXSize) const
{
	return cellXSize - _blockX + 1;
}

inline C_UINT32 HOG::BlockYSize(C_UINT32& cellYSize) const
{
	return cellYSize - _blockX + 1;
}
inline C_UINT32 HOG::BlockHisSize() const
{
	return _blockX * _blockY * _bin;
}

inline C_UINT32 HOG::CellHisTotalSize(C_UINT32& width, C_UINT32& height) const
{
	return CellXSize(width)
		* CellYSize(height)
		* _bin;
}

inline C_UINT32 HOG::BlockHisTotalSize(C_UINT32& width, C_UINT32& height) const
{
	return BlockXSize(CellXSize(width))
		* BlockYSize(CellYSize(height))
		* BlockHisSize();
}

void HOG::Gradient(C_UCHAR* src
	, C_UINT32 width, C_UINT32 height
	, double* amplitudes, double* angles)
{
	// 1. padding
	C_DOUBLE angle = 180.0 / MNDT::PI;
	C_UINT32 padWidth = width + 2;
	C_UINT32 padHeight = height + 2;
	UCHAR* padData = new UCHAR[padWidth * padHeight];
	
	MNDT::ImagePadding8bit(src, padData, width, height, 1);

	Image padImage(padData, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);

	// 2. calculate hog of gradient
	for (UINT32 row = 1; row < padHeight - 1; row++)
	{
		for (UINT32 col = 1; col < padWidth - 1; col++)
		{
			C_FLOAT Gx = static_cast<float>(padImage.image[row][col + 1])
				- static_cast<float>(padImage.image[row][col - 1]);

			C_FLOAT Gy = static_cast<float>(padImage.image[row + 1][col])
				- static_cast<float>(padImage.image[row - 1][col]);

			*angles = abs(atan2(Gy, Gx) * angle);
			*amplitudes = sqrt(Gx * Gx + Gy * Gy);

			angles++;
			amplitudes++;
		}
	}

	delete[] padData;
	padData = nullptr;
}

void HOG::GradienView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UINT32 size = width * height;
	double* amplitudes = new double[size];
	double* angles = new double[size];

	Gradient(src, width, height
		, amplitudes, angles);

	delete[] angles;
	angles = nullptr;

	UCHAR* endPur = pur + size;
	double* amplitudesPointer = amplitudes;

	while (pur < endPur)
	{
		*pur = static_cast<UCHAR>(*amplitudesPointer);

		pur++;
		amplitudesPointer++;
	}

	delete[] amplitudes;
	amplitudes = nullptr;
}

void HOG::HOGBlockView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	float* blockHistogram = new float[BlockHisTotalSize(width, height)];

	// step 1.2.3.4
	BlockHistogram(src, width, height
		, blockHistogram);




	C_UINT32 reWidth = FixWidth(width);
	C_UINT32 reHeight = FixHeight(height);
	C_UINT32 cellXSize = CellXSize(reWidth);
	C_UINT32 cellYSize = CellYSize(reHeight);
	C_UINT32 cellWidth = _bin * cellXSize;
	C_UINT32 blockHisSize = BlockHisSize();
	C_UINT32 blockXSize = BlockXSize(cellXSize);
	C_UINT32 blockYSize = BlockYSize(cellYSize);
	C_UINT32 cellHisTotalSize = CellHisTotalSize(width, height);
	C_FLOAT* blockHistogramPointer = blockHistogram;
	float* cellHistogram = new float[cellHisTotalSize] { 0.0f };
	UINT32* cellHisCount = new UINT32[cellHisTotalSize]{ 0 };

	// 5. calculate the block histogram to cell histogram
	for (UINT32 row = 0; row < blockYSize; row++)
	{
		for (UINT32 col = 0; col < blockXSize; col++)
		{
			HOGViewSum(blockHistogramPointer, cellWidth
				, cellHistogram, cellHisCount
				, col, row
				, col + _blockX, row + _blockY);
			blockHistogramPointer += blockHisSize;
		}
	}

	delete[] blockHistogram;
	blockHistogram = nullptr;


	// 6. calculate average of the cell histogram
	HOGViewAvg(cellHistogram, cellHisCount
		, cellHisTotalSize);

	delete[] cellHisCount;
	cellHisCount = nullptr;


	// 7. calculate normalization of the cell histogram
	HistogramNorm(cellHistogram
		, cellHisTotalSize, _bin
		, 1);


	// 8. draw for the cell histogram
	HOGDrawCell(pur
		, width, height
		, cellHistogram);

	delete[] cellHistogram;
	cellHistogram = nullptr;
}

void HOG::HOGCellView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UINT32 cellHisTotalSize = CellHisTotalSize(width, height);
	float* histogram = new float[cellHisTotalSize] { 0.0f };

	// step 1.2.3
	CellHistogram(src, width, height
		, histogram);

	// 4. normalization
	HistogramNorm(histogram
		, cellHisTotalSize, _bin
		, 1);

	// 5. draw
	HOGDrawCell(pur
		, width, height
		, histogram);

	delete[] histogram;
	histogram = nullptr;
}

void HOG::ReSize(C_UCHAR* src, UCHAR** resizeData
	, C_UINT32 width, C_UINT32 height)
{
	assert(*resizeData == nullptr);

	C_UINT32 reWidth = FixWidth(width);
	C_UINT32 reHeight = FixHeight(height);
	const bool resize = (reWidth - width) + (reHeight - height) != 0;

	if (resize)
	{
		*resizeData = new UCHAR[reWidth * reHeight];

		MNDT::Resize8bit(src, *resizeData
			, width, height
			, reWidth, reHeight
			, MNDT::ResizeType::NEAREST);
	}
	else
	{
		*resizeData = const_cast<UCHAR*>(src);
	}
}

void HOG::CellHistogram(C_UCHAR* src, C_UINT32 width, C_UINT32 height
	, float* histogram)
{
	// 1. fix size
	UCHAR* resizeData = nullptr;

	ReSize(src, &resizeData, width, height);



	// 2. get gradient
	C_UINT32 reWidth = FixWidth(width);
	C_UINT32 reHeight = FixHeight(height);
	C_UINT32 size = reWidth * reHeight;
	double* amplitudes = new double[size];
	double* angles = new double[size];

	Gradient(resizeData, reWidth, reHeight
		, amplitudes, angles);

	delete[] amplitudes;
	amplitudes = nullptr;

	if (resizeData != src)
	{
		delete[] resizeData;
		resizeData = nullptr;
	}



	// 3. calculate histogram
	for (UINT32 row = 0; row < reHeight; row += _cellY)
	{
		for (UINT32 col = 0; col < reWidth; col += _cellX)
		{
			CalcCellHistogram(angles, reWidth
				, histogram
				, col, row
				, col + _cellX, row + _cellY);
			histogram += _bin;
		}
	}

	delete[] angles;
	angles = nullptr;

}

void HOG::CalcCellHistogram(C_DOUBLE* angles, C_UINT32 width
	, float* histogram
	, C_UINT32 sWidth, C_UINT32 sHeight
	, C_UINT32 eWidth, C_UINT32 eHeight)
{
	// bin is 9
	C_DOUBLE space = 20.0;

	for (UINT32 row = sHeight; row < eHeight; row++)
	{
		C_UINT32 rowIndex = row * width;

		for (UINT32 col = sWidth; col < eWidth; col++)
		{
			int32_t binIndex = static_cast<int32_t>(ceil(angles[rowIndex + col] / space)) - 1;

			binIndex = binIndex < 0 ? 0 : binIndex;
			histogram[binIndex]++;
		}
	}
}

void HOG::HistogramNorm(float* histogram
	, C_UINT32 hisTotalSize, C_UINT32 hisSIze
	, C_UINT32 base)
{
	for (UINT32 index = 0; index < hisTotalSize; index += hisSIze)
	{
		MNDT::SetNormalizedHistogram8bit(histogram, hisSIze, static_cast<float>(base));
		histogram += hisSIze;
	}
}

void HOG::HistogramNorm2(float* histogram
	, C_UINT32 hisTotalSize, C_UINT32 hisSIze)
{
	for (UINT32 index = 0; index < hisTotalSize; index += hisSIze)
	{
		MNDT::SetNormalizedHistogram8bit(histogram, hisSIze, MNDT::Normalized::L2);
		histogram += hisSIze;
	}
}

void HOG::HOGDrawCell(UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, float* cellHistogram)
{
	C_UINT32 reWidth = FixWidth(width);
	C_UINT32 reHeight = FixHeight(height);
	C_UINT32 cellXSize = CellXSize(reWidth);
	C_UINT32 cellYSize = CellYSize(reHeight);
	C_UINT32 offsetX = _cellX >> 1;
	C_UINT32 offsetY = _cellY >> 1;
	Image purImgae(pur, reWidth, reHeight, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = 0; row < cellYSize; row++)
	{
		C_UINT32 centerY = row * _cellY + offsetY - 1;

		for (UINT32 col = 0; col < cellXSize; col++)
		{
			C_UINT32 centerX = col * _cellX + offsetX - 1;
			Point centerPoint(centerX, centerY);

			for (UINT32 index = 0; index < _bin; index++)
			{
				C_FLOAT x = centerX + static_cast<float>(offsetX * cellHistogram[index] * MNDT::FixValue(cos(2.0 * MNDT::PI * index / _bin)));
				C_FLOAT y = centerY + static_cast<float>(offsetY * cellHistogram[index] * MNDT::FixValue(sin(2.0 * MNDT::PI * index / _bin)));
				if (x < 0)
				{
					int i = 0;
				}
				Point binPoint(static_cast<UINT32>(x), static_cast<UINT32>(y));

				MNDT::DrawLine8bit(purImgae, centerPoint, binPoint);
			}
			cellHistogram += _bin;
		}
	}
}

void HOG::BlockHistogram(C_UCHAR* src, C_UINT32 width, C_UINT32 height
	, float* histogram)
{
	C_UINT32 reWidth = FixWidth(width);
	C_UINT32 reHeight = FixHeight(height);
	C_UINT32 cellXSize = CellXSize(reWidth);
	C_UINT32 cellYSize = CellYSize(reHeight);
	float* cellHistogram = new float[CellHisTotalSize(reWidth, reHeight)]{ 0 };

	// step 1.2.3
	CellHistogram(src, width, height
		, cellHistogram);

	// 4. copy the cell histogram to the block histogram
	C_UINT32 cellWidth = _bin * cellXSize;
	C_UINT32 blockHisSize = BlockHisSize();
	C_UINT32 blockXSize = BlockXSize(cellXSize);
	C_UINT32 blockYSize = BlockYSize(cellYSize);

	for (UINT32 row = 0; row < blockYSize; row++)
	{
		for (UINT32 col = 0; col < blockXSize; col++)
		{
			CalcBlockHistogram(cellHistogram, cellWidth
				, histogram
				, col, row
				, col + _blockX, row + _blockY);
			//MNDT::SetNormalizedHistogram8bit(histogram, blockHisSize, MNDT::Normalized::L2);
			histogram += blockHisSize;
		}
	}

	delete[] cellHistogram;
	cellHistogram = nullptr;
}

void HOG::CalcBlockHistogram(C_FLOAT* cellHistogram, C_UINT32 cellWidth
	, float* histogram
	, C_UINT32 sCellX, C_UINT32 sCellY
	, C_UINT32 eCellX, C_UINT32 eCellY)
{
	C_UINT32 copySize = _bin * sizeof(float);

	for (UINT32 row = sCellY; row < eCellY; row++)
	{
		C_UINT32 rowIndex = row * cellWidth;

		for (UINT32 col = sCellX; col < eCellX; col++)
		{
			C_UINT32 index = rowIndex + col * _bin;
			memcpy(histogram, cellHistogram + index, copySize);
			histogram += _bin;
		}
	}
}

void HOG::HOGViewSum(C_FLOAT* blockHistogram, C_UINT32 cellXSize
	, float* cellHistogram
	, UINT32* cellHisCount
	, C_UINT32 sCellX, C_UINT32 sCellY
	, C_UINT32 eCellX, C_UINT32 eCellY)
{
	for (UINT32 row = sCellX; row < eCellX; row++)
	{
		C_UINT32 rowIndex = row * cellXSize;

		for (UINT32 col = sCellY; col < eCellY; col++)
		{
			C_UINT32 index = rowIndex + col * _bin;

			for (UINT32 binIndex = 0; binIndex < _bin; binIndex++)
			{
				*(cellHistogram + index + binIndex) += *(blockHistogram + binIndex);
				*(cellHisCount + index + binIndex) += 1;
			}
			blockHistogram += _bin;
		}
	}
}

void HOG::HOGViewAvg(float* cellHistogram, C_UINT32* cellHisCount
	, C_UINT32 cellTotalSize)
{
	C_FLOAT* cellHistogramEnd = cellHistogram + cellTotalSize;

	while (cellHistogram < cellHistogramEnd)
	{
		*cellHistogram /= *cellHisCount;
		cellHistogram++;
		cellHisCount++;
	}
}