#ifdef MNDTLIBRARY_EXPORTS
#define MNDTLIBRARY_API __declspec(dllexport)
#include "Library.h"
#include "LBP.h"
#include "HOG.h"
#include "Segment.h"
#include "Hough.h"

extern "C" MNDTLIBRARY_API void mndtWrite(C_UCHAR* msg)
{
	MNDT::Write(msg);
}

extern "C" MNDTLIBRARY_API void mndtChangeColor(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 type)
{
	
	MNDT::ChangeColor(src, pur
		, width, height
		, type);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentHSV(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 H, C_INT32 S, C_INT32 V)
{
	
	MNDT::AdjustmentHSV(src, pur
		, width, height
		, H, S, V);
}

extern "C" MNDTLIBRARY_API void mndtAdjustmentYCbCr(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 Y, C_INT32 Cb, C_INT32 Cr)
{
	
	MNDT::AdjustmentYCbCr(src, pur
		, width, height
		, Y, Cb, Cr);
}

extern "C" MNDTLIBRARY_API void mndtImagePadding8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 pad)
{
	
	MNDT::ImagePadding8bit(src, pur
		, width, height
		, pad);
}

extern "C" MNDTLIBRARY_API void mndtImagePadding24bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 pad)
{
	
	MNDT::ImagePadding24bit(src, pur
		, width, height
		, pad);
}

extern "C" MNDTLIBRARY_API void mndtBlur8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	
	MNDT::Blur8bit(src, pur
		, width, height
		, size);
}

extern "C" MNDTLIBRARY_API void mndtBlurGauss8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size, C_FLOAT sigma)
{
	
	MNDT::BlurGauss8bit(src, pur
		, width, height
		, size, sigma);
}

extern "C" MNDTLIBRARY_API void mndtBlurGauss24bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size, C_FLOAT sigma)
{
	
	MNDT::BlurGauss24bit(src, pur
		, width, height
		, size, sigma);
}

extern "C" MNDTLIBRARY_API void mndtMedianBlur8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	
	MNDT::MedianBlur8bit(src, pur
		, width, height
		, size);
}

extern "C" MNDTLIBRARY_API void mndtBilateralBlur8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT spaceSigma, C_FLOAT colorSigma
	, C_UINT32 size)
{
	
	MNDT::BilateralBlur8bit(src, pur
		, width, height
		, spaceSigma, colorSigma
		, size);
}

extern "C" MNDTLIBRARY_API void mndtHistogram8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	MNDT::Histogram8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtHistogramEqualization8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	MNDT::HistogramEqualization8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API double mndtCompareHistogram(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	return MNDT::CompareHistogram(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtChannel(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 channel)
{
	
	MNDT::Channel(src, pur
		, width, height
		, channel);
}

extern "C" MNDTLIBRARY_API void mndtBackProjection(C_UCHAR* src, UCHAR* pur
	, C_UINT32 srcWidth, C_UINT32 srcHeight
	, C_UINT32* histogram
	, C_UCHAR minRange, C_UCHAR maxRange
	, C_UCHAR bin)
{
	
	MNDT::BackProjection(src, pur
		, srcWidth, srcHeight
		, histogram
		, minRange, maxRange
		, bin);
}

extern "C" MNDTLIBRARY_API void mndtSetHistogram8bit(C_UCHAR* src, int32_t* histogram
	, C_UINT32 hisWidth, C_UINT32 hisHeight
	, C_UCHAR minRange, C_UCHAR maxRange
	, C_UCHAR bin)
{
	
	MNDT::SetHistogram8bit(src, histogram
		, hisWidth, hisHeight
		, minRange, maxRange
		, bin);
}

extern "C" MNDTLIBRARY_API void mndtSetNormalizedHistogram8bit(int32_t* histogram
	, C_UINT32 bin
	, C_UCHAR maxRange)
{
	
	MNDT::SetNormalizedHistogram8bit(histogram
		, bin
		, maxRange);
}

extern "C" MNDTLIBRARY_API void mndtThreshold8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 thresh)
{
	
	MNDT::Threshold8bit(src, pur
		, width, height
		, thresh);
}

extern "C" MNDTLIBRARY_API void mndtMeanShift(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32* rectPoint
	, C_UINT32 times
	, C_DOUBLE threshold)
{
	
	MNDT::MeanShift(src, pur
		, width, height
		, rectPoint
		, times
		, threshold);
}

extern "C" MNDTLIBRARY_API void mndtRotate8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 type)
{
	
	MNDT::Rotate8bit(src, pur
		, width, height
		, static_cast<MNDT::RotateType>(type));
}

extern "C" MNDTLIBRARY_API void mndtResize8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 reWidth, C_UINT32 reHeight
	, C_UINT32 type)
{
	
	MNDT::Resize8bit(src, pur
		, width, height
		, reWidth, reHeight
		, (MNDT::ResizeType)type);
}

extern "C" MNDTLIBRARY_API void mndtPyramidDown8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	MNDT::PyramidDown8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtPyramidUp8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	MNDT::PyramidUp8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtSetAffineTransform(C_FLOAT* affine
	, float* baseX, float* baseY
	, C_UINT32 row, C_UINT32 col)
{
	float** affine2D = new float*[row];

	for (UINT32 index = 0; index < row; index++)
	{
		affine2D[index] = new float[col];
		memcpy(affine2D[index], affine, col * sizeof(C_FLOAT));
		affine += col;
	}

	
	MNDT::SetAffineTransform(affine2D
		, baseX, baseY
		, row, col);

	for (UINT32 index = 0; index < row; index++)
	{
		delete[] affine2D[index];
		affine2D[index] = nullptr;
	}

	delete[] affine2D;
	affine2D = nullptr;
}

extern "C" MNDTLIBRARY_API void mndtAffine8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, float* baseX, float* baseY)
{
	
	MNDT::Affine8bit(src, pur
		, width, height
		, baseX, baseY);
}

extern "C" MNDTLIBRARY_API void mndtSobel24bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, const bool dx, const bool dy)
{
	
	MNDT::SobelVisualization24bit(src, pur
		, width, height
		, dx, dy);
}

extern "C" MNDTLIBRARY_API void mndtSobelEdge8bit(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	
	MNDT::SobelEdgeView8bit(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtSegmentImage(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize
	, UINT32* numCss)
{
	Segment segment;
	GraphTree* graphTree = new GraphTree(width * height);

	segment.SegmentImage(src, pur
		, width, height
		, sigma, threshold, minSize
		, graphTree);
	*numCss = graphTree->NumSets();


	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);

	segment.Visualization(purImage, graphTree);

	delete graphTree;
	graphTree = nullptr;
}

extern "C" MNDTLIBRARY_API void mndtSelectiveSearch(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize
	, UINT32* numCss)
{
	Segment segment;

	segment.SelectiveSearch(src, pur
		, width, height
		, sigma, threshold, minSize);
}

extern "C" MNDTLIBRARY_API void mndtOriginalLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.OriginalLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtCircularLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.CircularLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtInvariantLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.InvariantLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtEquivalentLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.EquivalentLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtMultiScaleBlockLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.MultiScaleBlockLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtSEMultiScaleBlockLBP(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	LBP lbp;

	lbp.SEMultiScaleBlockLBP(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtLBPHistogram(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 gridX, C_UINT32 gridY
	, C_UINT32 bin)
{
	LBP lbp;

	lbp.LBPHistogram(src, pur
		, width, height
		, gridX, gridY
		, bin);
}

extern "C" MNDTLIBRARY_API void mndtGamma(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_DOUBLE gamma)
{
	

	MNDT::Gamma8bit(src, pur
		, width, height
		, gamma);
}

extern "C" MNDTLIBRARY_API void mndtHOGGradient(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height)
{
	HOG hog;

	hog.GradienView(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtHOGCellHistogram(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 cellX, C_UINT32 cellY)
{
	HOG hog;

	float* histogram = new float[hog.CellHisTotalSize(width, height)]{ 0 };

	hog.CellHistogram(src, width, height
		, histogram);

	delete[] histogram;
	histogram = nullptr;
}

extern "C" MNDTLIBRARY_API void mndtHOGBlockHistogram(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 cellX, C_UINT32 cellY
	, C_UINT32 blockX, C_UINT32 blockY)
{
	HOG hog;
	float* histogram = new float[hog.BlockHisTotalSize(width, height)]{ 0 };

	hog.BlockHistogram(src, width, height
		, histogram);

	delete[] histogram;
	histogram = nullptr;
}


extern "C" MNDTLIBRARY_API void mndtHOGView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 cellX, C_UINT32 cellY
	, C_UINT32 blockX, C_UINT32 blockY)
{
	HOG hog(cellX, cellY, blockX, blockY);

	hog.HOGBlockView(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtHOGCellView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 cellX, C_UINT32 cellY)
{
	HOG hog(cellX, cellY);

	hog.HOGCellView(src, pur
		, width, height);
}

extern "C" MNDTLIBRARY_API void mndtHOGBlockView(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 cellX, C_UINT32 cellY
	, C_UINT32 blockX, C_UINT32 blockY)
{
	HOG hog(cellX, cellY, blockX, blockY);

	hog.HOGBlockView(src, pur
		, width, height);
}


extern "C" MNDTLIBRARY_API void mndtHoughLines(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT rho, C_FLOAT theta, C_UINT32 threshold)
{
	

	MNDT::HoughLines(src, pur
		, width, height
		, rho, theta, threshold);
}

extern "C" MNDTLIBRARY_API void mndtHoughCircles(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT minRadius, C_FLOAT maxRadius, C_UINT32 threshold)
{
	

	MNDT::HoughCircles(src, pur
		, width, height
		, minRadius, maxRadius, threshold);
}

#else
#define MNDTLIBRARY_API __declspec(dllimport)
#endif