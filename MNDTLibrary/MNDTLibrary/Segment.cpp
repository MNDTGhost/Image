#include "Segment.h"

void Segment::SegmentImage(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize
	, GraphTree* graphTree)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	assert(graphTree != nullptr);
	assert(graphTree->NumSets() == width * height);

	C_UINT32 size = static_cast<int>(ceil(4 * sigma)) + 1;
	Library lib;

	lib.BlurGauss24bit(src, pur
		, width, height
		, size, sigma);

	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);
	Edge* edges = new Edge[width * height * 4];
	UINT32 edgeSize = 0;

	// 取得每個點的左和上排連結
	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			UINT32 nowIndex = row * width + col;
			Pixel nowPix = purImage.GetPixel(row, col);
			Edge* edge = nullptr;

			//// right
			//if (col < width - 1)
			//{
			//	edge = &edges[edgeSize];
			//	edge->centerIndex = nowIndex;
			//	edge->linkIndex = row * width + col + 1;
			//	edge->weights = Diff(nowPix, purImage.GetPixel(row, col + 1));
			//	edgeSize++;
			//}

			//// top left
			//if (row < height - 1)
			//{
			//	edge = &edges[edgeSize];
			//	edge->centerIndex = nowIndex;
			//	edge->linkIndex = (row + 1) * width + col;
			//	edge->weights = Diff(nowPix, purImage.GetPixel(row + 1, col));
			//	++edgeSize;
			//}

			//// top right
			//if ((col < width - 1) && (row < height - 1))
			//{
			//	edge = &edges[edgeSize];
			//	edge->centerIndex = nowIndex;
			//	edge->linkIndex = (row + 1) * width + col + 1;
			//	edge->weights = Diff(nowPix, purImage.GetPixel(row + 1, col + 1));
			//	++edgeSize;
			//}

			//// left
			//if ((col < width - 1) && (row > 0))
			//{
			//	edge = &edges[edgeSize];
			//	edge->centerIndex = nowIndex;
			//	edge->linkIndex = (row - 1) * width + col + 1;
			//	edge->weights = Diff(nowPix, purImage.GetPixel(row - 1, col + 1));
			//	++edgeSize;
			//}
			// top
			if (row > 0)
			{
				edge = &edges[edgeSize];
				edge->centerIndex = nowIndex;
				edge->linkIndex = (row - 1) * width + col;
				edge->weights = Diff(nowPix, purImage.GetPixel(row - 1, col));
				edgeSize++;
			}

			// top left
			if (row > 0 && col > 0)
			{
				edge = &edges[edgeSize];
				edge->centerIndex = nowIndex;
				edge->linkIndex = (row - 1) * width + col - 1;
				edge->weights = Diff(nowPix, purImage.GetPixel(row - 1, col - 1));
				++edgeSize;
			}

			// top right
			if (row > 0 && col < width - 1)
			{
				edge = &edges[edgeSize];
				edge->centerIndex = nowIndex;
				edge->linkIndex = (row - 1) * width + col + 1;
				edge->weights = Diff(nowPix, purImage.GetPixel(row - 1, col + 1));
				++edgeSize;
			}

			// left
			if (col > 0)
			{
				edge = &edges[edgeSize];
				edge->centerIndex = nowIndex;
				edge->linkIndex = row * width + col - 1;
				edge->weights = Diff(nowPix, purImage.GetPixel(row, col - 1));
				++edgeSize;
			}
		}
	}



	// 連通法
	SegmentGraph(graphTree
		, edges, edgeSize
		, threshold);

	// 合併小於最小尺寸
	for (UINT32 index = 0; index < edgeSize; index++)
	{
		const Edge& edge = edges[index];
		C_UINT32 centerIndex = graphTree->Find(edge.centerIndex);
		C_UINT32 linkIndex = graphTree->Find(edge.linkIndex);

		if (centerIndex != linkIndex
			&& (graphTree->GetSize(centerIndex) < minSize || graphTree->GetSize(linkIndex) < minSize))
		{
			graphTree->Merge(centerIndex, linkIndex);
		}
	}

	delete[] edges;
	edges = nullptr;
}

void Segment::SegmentGraph(GraphTree* graphTree
	, Edge* edges, C_UINT32 edgeSize
	, C_FLOAT threshold)
{
	std::sort(edges, edges + edgeSize
		, [](const Edge& edge1, const Edge& edge2) { return edge1.weights < edge2.weights; });

	double* thresholds = new double[graphTree->NumSets()];

	for (UINT32 index = 0; index < graphTree->NumSets(); index++)
	{
		thresholds[index] = Threshold(threshold, 1);
	}

	for (UINT32 index = 0; index < edgeSize; index++)
	{
		const Edge& edge = edges[index];
		UINT32 centerIndex = graphTree->Find(edge.centerIndex);
		C_UINT32 linkIndex = graphTree->Find(edge.linkIndex);

		if (centerIndex != linkIndex
			&& edge.weights < thresholds[centerIndex]
			&& edge.weights < thresholds[linkIndex])
		{
			graphTree->Merge(centerIndex, linkIndex);
			centerIndex = graphTree->Find(centerIndex);
			thresholds[centerIndex] = edge.weights + Threshold(threshold, static_cast<float>(graphTree->GetSize(centerIndex)));
		}
	}

	delete[] thresholds;
	thresholds = nullptr;
}

void Segment::Visualization(Image& image
	, GraphTree* graphTree)
{
	C_UINT32 size = image.Height() * image.Width();
	Pixel *pixs = new Pixel[size];

	for (UINT32 index = 0; index < size; index++)
	{
		pixs[index] = GetColor();
	}


	for (UINT32 row = 0; row < image.Height(); row++)
	{
		for (UINT32 col = 0; col < image.Width(); col++)
		{
			UINT32 index = graphTree->Find(row * image.Width() + col);
			image.SetPixel(row, col, pixs[index]);
		}
	}

	delete[] pixs;
	pixs = nullptr;
}

void Segment::SelectiveSearch(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize)
{
	GraphTree* graphTree = new GraphTree(width * height);
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::BGR_24BIT);

	SegmentImage(src, pur
		, width, height
		, sigma, threshold, minSize
		, graphTree);

	std::map<UINT32, Region> R = ExtractRegion(srcImage, graphTree);

	delete graphTree;
	graphTree = nullptr;
}

void Segment::CalcSize(const Image& image
	, Region& region
	, GraphTree* graphTree)
{
	C_UINT32 width = image.Width();
	C_UINT32 maxHeight = region.rect.EndY();
	C_UINT32 maxWidth = region.rect.EndX();

	for (UINT32 row = region.rect.Y(); row < maxHeight; row++)
	{
		for (UINT32 col = region.rect.X(); col < maxWidth; col++)
		{
			C_UINT32 label = graphTree->Find(row * width + col);

			if (label == region.label)
			{
				region.size++;
			}
		}
	}
}

void Segment::CalcTextureGradient(const Image& image, float* angle)
{
	Library lib;
	int32_t* Gx = new int32_t[image.Width() * image.Height() * 3];
	int32_t* Gy = new int32_t[image.Width() * image.Height() * 3];

	lib.Sobel24bit(image.data, Gx
		, image.Width(), image.Height()
		, true, false);

	lib.Sobel24bit(image.data, Gy
		, image.Width(), image.Height()
		, false, true);

	float* magnitude = new float[image.Width() * image.Height() * 3];

	lib.CartToPolar24bit(Gx, Gy
		, image.Width(), image.Height()
		, magnitude, angle);

	delete[] Gx;
	Gx = nullptr;

	delete[] Gy;
	Gy = nullptr;

	delete[] magnitude;
	magnitude = nullptr;
}

void Segment::CalcColourHist(const Image& hsv
	, Region& region
	, GraphTree* graphTree)
{
	assert(region.colorHist == nullptr);

	C_UINT32 regionWidth = region.size * 3;
	UCHAE* hsvData = new UCHAE[regionWidth];
	Image hsvImage(hsvData, regionWidth, 1, MNDT::ImageType::BGR_24BIT);
	UINT32 hsvIndex = 0;

	C_UINT32 width = hsv.Width();
	C_UINT32 maxHeight = region.rect.EndY();
	C_UINT32 maxWidth = region.rect.EndX();

	for (UINT32 row = region.rect.Y(); row < maxHeight; row++)
	{
		for (UINT32 col = region.rect.X(); col < maxWidth; col++)
		{
			C_UINT32 label = graphTree->Find(row * width + col);

			if (label == region.label)
			{
				Pixel pix = hsv.GetPixel(row, col);
				hsvImage.SetPixel(0, hsvIndex, pix);
				hsvIndex++;
			}
		}
	}

	C_UINT32 bin = 25;
	Library lib;
	region.colorHist = new float[bin * 3]{ 0 };

	lib.SetHistogram24bit(hsvData, region.colorHist, region.size, 1, 0, 255, bin);
	lib.SetNormalizedHistogram24bit(region.colorHist, bin);

	delete[] hsvData;
	hsvData = nullptr;
}

// 依據紋理分為8個方位在計算每個分為10個直方圖
void Segment::CalcTextureHist(const Image& image
	, C_FLOAT* angle
	, Region& region
	, GraphTree* graphTree)
{
	assert(region.textureHist == nullptr);

	C_UINT32 orientations = 8;
	C_UINT32 bin = 10;
	C_UCHAE interval = 255 / bin;
	C_UINT32 width = image.Width();
	C_UINT32 maxHeight = region.rect.EndY();
	C_UINT32 maxWidth = region.rect.EndX();
	C_UINT32 diff = orientations * bin;

	region.textureHist = new float[orientations * bin * 3]{ 0.0f };

	for (UINT32 row = region.rect.Y(); row < maxHeight; row++)
	{
		for (UINT32 col = region.rect.X(); col < maxWidth; col++)
		{
			C_UINT32 label = graphTree->Find(row * width + col);

			if (label == region.label)
			{
				UINT32 offset = row * width * 3 + col;
				UINT32 BPosition = static_cast<UINT32>(*(angle + offset) / 22.5) % orientations;
				UINT32 GPosition = static_cast<UINT32>(*(angle + offset + 1) / 22.5) % orientations;
				UINT32 RPosition = static_cast<UINT32>(*(angle + offset + 2) / 22.5) % orientations;

				Pixel pix = image.GetPixel(row, col);
				UINT32 BBin = (pix.B / interval) % bin;
				UINT32 GBin = (pix.G / interval) % bin;
				UINT32 RBin = (pix.R / interval) % bin;

				region.textureHist[BPosition * BBin + BBin]++;
				region.textureHist[GPosition * GBin + GBin + diff]++;
				region.textureHist[RPosition * RBin + RBin + diff + diff]++;
			}
		}
	}

	Library lib;

	for (UINT32 index = 0; index < orientations; index++)
	{
		lib.SetNormalizedHistogram8bit(region.textureHist + index * bin, bin);
		lib.SetNormalizedHistogram8bit(region.textureHist + index * bin + diff, bin);
		lib.SetNormalizedHistogram8bit(region.textureHist + index * bin + diff + diff, bin);
	}


}

std::map<UINT32, Region> Segment::ExtractRegion(const Image& image
	, GraphTree* graphTree)
{
	C_UINT32 width = image.Width();
	C_UINT32 height = image.Height();
	std::map<UINT32, Region> R;

	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			C_UINT32 label = graphTree->Find(row * width + col);

			if (R.find(label) == R.end())
			{
				R[label] = Region(label);
			}

			Rect& rect = R[label].rect;

			if (rect.X() > col)
			{
				rect.X(col);
			}

			if (rect.Y() > row)
			{
				rect.Y(row);
			}

			if (rect.EndX() < col + 1)
			{
				rect.Width(col - rect.X() + 1);
			}

			if (rect.EndY() < row + 1)
			{
				rect.Height(row - rect.Y() + 1);
			}
		}
	}

	float* angle = new float[width * height * 3];

	CalcTextureGradient(image, angle);


	Library lib;
	UCHAE* hsv = new UCHAE[width * height * 3];
	Image hsvImage(hsv, width, height, MNDT::ImageType::BGR_24BIT);

	lib.ChangeColor(image.data, hsv
		, width, height
		, ColerType::BGR2HSV);

	for (std::map<UINT32, Region>::iterator item = R.begin(); item != R.end(); item++)
	{
		Region& region = item->second;

		CalcSize(image, region, graphTree);
		CalcColourHist(hsvImage, region, graphTree);
		CalcTextureHist(image, angle, region, graphTree);
	}

	delete[] angle;
	angle = nullptr;

	delete[] hsv;
	hsv = nullptr;

	return R;
}