#include "Segment.h"

void Segment::SegmentImage(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize
	, GraphTree* graphTree)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	assert(graphTree != nullptr);
	assert(graphTree->NumSets() == width * height);

	C_UINT32 size = static_cast<UINT32>(ceil(4 * sigma)) + 1;

	MNDT::BlurGauss24bit(src, pur
		, width, height
		, size, sigma);

	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);
	Edge* edges = new Edge[width * height * 4];
	UINT32 edgeSize = 0;

	// 1. get neighbors
	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			UINT32 nowIndex = row * width + col;
			Pixel nowPix = purImage.GetPixel(row, col);
			Edge* edge = nullptr;

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



	// step 2.3
	// 連通法
	SegmentGraph(graphTree
		, edges, edgeSize
		, threshold);

	// 4. merge region if the region is smaller than minSize params
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
	// 2. sort
	std::sort(edges, edges + edgeSize
		, [](const Edge& edge1, const Edge& edge2) { return edge1.weights < edge2.weights; });

	double* thresholds = new double[graphTree->NumSets()];

	for (UINT32 index = 0; index < graphTree->NumSets(); index++)
	{
		thresholds[index] = Threshold(threshold, 1);
	}

	// 3. merge region
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


void Segment::SelectiveSearch(C_UCHAR* src, UCHAR* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize)
{
	GraphTree* graphTree = new GraphTree(width * height);
	Image srcImage(const_cast<UCHAR*>(src), width, height, MNDT::ImageType::BGR_24BIT);


	SegmentImage(src, pur
		, width, height
		, sigma, threshold, minSize
		, graphTree);

	std::map<UINT32, Region> R = ExtractRegion(srcImage, graphTree);
	std::vector<Neighbour> neighbours = ExtractNeighbours(R);
	std::unordered_map<Neighbour, double> S;
	C_UINT32 imgSize = width * height;

	for (auto &neighbour : neighbours)
	{
		S[neighbour] = CalcSimilarity(R[neighbour.first], R[neighbour.second]
			, imgSize);
	}

	while (!S.empty())
	{
		auto compare = [](const std::pair<Neighbour, double > n1, const std::pair<Neighbour, double > n2) { return n1.second < n2.second; };
		auto maxNode = std::max_element(S.begin(), S.end(), compare);

		UINT32 label1 = maxNode->first.first;
		UINT32 label2 = maxNode->first.second;
		UINT32 newLabel = R.rbegin()->first + 1;
		Neighbour nowNeighbour = std::make_pair(label1, label2);

		R[newLabel] = Region();
		MergeRegions(R[newLabel], R[label1], R[label2], newLabel);

		std::vector<Neighbour> keyToDelete;

		for (auto& node : S)
		{
			const Neighbour& neighbour = node.first;

			if (neighbour.first == label1
				|| neighbour.second == label1
				|| neighbour.first == label2
				|| neighbour.second == label2)
			{
				keyToDelete.push_back(neighbour);
			}
		}

		for (auto& key : keyToDelete)
		{
			S.erase(key);

			if (key == nowNeighbour)
			{
				continue;
			}

			UINT32 noDeleteLabel = (key.first == label1 || key.first == label2) ? key.second : key.first;
			S[std::make_pair(noDeleteLabel, newLabel)] = CalcSimilarity(R[noDeleteLabel], R[newLabel], imgSize);
		}
	}

	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);

	for (auto& node : R)
	{
		const Rect& rect = node.second.rect;
		C_FLOAT diff = static_cast<float>(rect.Width()) / rect.Height();

		if (diff > 0.6 && diff < 1.4)
		{
			MNDT::DrawRect24bit(purImage, rect, Pixel(255, 50, 50));
		}
	}

	delete graphTree;
	graphTree = nullptr;
}

void Segment::CalcSize(const Image& image
	, Region& region
	, GraphTree* graphTree)
{
	C_UINT32 width = image.Width();
	C_UINT32 maxHeight = region.rect.EndY() + 1;
	C_UINT32 maxWidth = region.rect.EndX() + 1;

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
	int32_t* Gx = new int32_t[image.Width() * image.Height() * 3];
	int32_t* Gy = new int32_t[image.Width() * image.Height() * 3];

	MNDT::Sobel24bit(image.data, Gx
		, image.Width(), image.Height()
		, true, false);

	MNDT::Sobel24bit(image.data, Gy
		, image.Width(), image.Height()
		, false, true);

	float* magnitude = new float[image.Width() * image.Height() * 3];

	MNDT::CartToPolar(Gx, Gy
		, image.Width(), image.Height()
		, magnitude, angle
		, MNDT::ImageType::BGR_24BIT);

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
	UCHAR* hsvData = new UCHAR[regionWidth];
	Image hsvImage(hsvData, regionWidth, 1, MNDT::ImageType::BGR_24BIT);
	UINT32 hsvIndex = 0;

	C_UINT32 width = hsv.Width();
	C_UINT32 maxHeight = region.rect.EndY() + 1;
	C_UINT32 maxWidth = region.rect.EndX() + 1;

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

	region.colorHist = new float[bin * 3]{ 0 };

	MNDT::SetHistogram24bit(hsvData, region.colorHist, region.size, 1, 0, 255, bin);
	MNDT::SetNormalizedHistogram24bit(region.colorHist, bin);

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
	C_UCHAR interval = 255 / bin;
	C_UINT32 width = image.Width();
	C_UINT32 maxHeight = region.rect.EndY() + 1;
	C_UINT32 maxWidth = region.rect.EndX() + 1;
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

	for (UINT32 index = 0; index < orientations; index++)
	{
		MNDT::SetNormalizedHistogram8bit(region.textureHist + index * bin, bin, MNDT::Normalized::L1);
		MNDT::SetNormalizedHistogram8bit(region.textureHist + index * bin + diff, bin, MNDT::Normalized::L1);
		MNDT::SetNormalizedHistogram8bit(region.textureHist + index * bin + diff + diff, bin, MNDT::Normalized::L1);
	}


}

std::map<UINT32, Region> Segment::ExtractRegion(const Image& image
	, GraphTree* graphTree)
{
	C_INT32 width = image.Width();
	C_INT32 height = image.Height();
	std::map<UINT32, Region> R;

	for (int32_t row = 0; row < height; row++)
	{
		for (int32_t col = 0; col < width; col++)
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

			if (rect.EndX() < col)
			{
				rect.Width(col - rect.X() + 1);
			}

			if (rect.EndY() < row)
			{
				rect.Height(row - rect.Y() + 1);
			}
		}
	}

	float* angle = new float[width * height * 3];

	CalcTextureGradient(image, angle);

	UCHAR* hsv = new UCHAR[width * height * 3];
	Image hsvImage(hsv, width, height, MNDT::ImageType::BGR_24BIT);

	MNDT::ChangeColor(image.data, hsv
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

inline bool Segment::Intersecting(const Region &region1, const Region &region2) const
{
	return ((region1.rect & region2.rect).Area() > 0);
}

std::vector<Neighbour> Segment::ExtractNeighbours(const std::map<UINT32, Region>& R)
{
	std::vector<Neighbour> neighbours;

	// 全部最多組合
	neighbours.reserve((R.size() * (R.size() - 1)) >> 1);

	for (auto region1 = R.cbegin(); region1 != R.cend(); region1++)
	{
		auto temp = region1;
		temp++;

		for (auto region2 = temp; region2 != R.cend(); region2++)
		{
			if (Intersecting(region1->second, region2->second))
			{
				C_UINT32 min = std::min(region1->first, region2->first);
				C_UINT32 max = std::max(region1->first, region2->first);

				neighbours.push_back(std::make_pair(min, max));
			}
		}
	}
	return neighbours;
}

double Segment::CalcSimOfColor(const Region &region1, const Region &region2)
{
	C_UINT32 bin = 25;
	C_UINT32 size = bin * 3;
	double sum = 0.0;

	for (UINT32 index = 0; index < size; index++)
	{
		sum += std::min(*(region1.colorHist + index), *(region2.colorHist + index));
	}

	return sum;
}

double Segment::CalcSimOfTexture(const Region &region1, const Region &region2)
{
	C_UINT32 orientations = 8;
	C_UINT32 bin = 10;
	C_UINT32 size = orientations * bin * 3;
	double sum = 0.0;

	for (UINT32 index = 0; index < size; index++)
	{
		sum += std::min(*(region1.textureHist + index), *(region2.textureHist + index));
	}

	return sum;
}

inline double Segment::CalcSimOfSize(const Region &region1, const Region &region2
	, C_UINT32 imgSize)
{
	return 1.0 - static_cast<double>((region1.size + region2.size)) / imgSize;
}

inline double Segment::CalcSimOfRect(const Region &region1, const Region &region2
	, C_UINT32 imgSize)
{
	return 1.0 - static_cast<double>(((region1.rect | region2.rect).Area() - region1.size - region2.size)) / imgSize;
}

inline double Segment::CalcSimilarity(const Region &region1, const Region &region2
	, C_UINT32 imgSize)
{
	return (CalcSimOfColor(region1, region2)
		+ CalcSimOfTexture(region1, region2)
		+ CalcSimOfSize(region1, region2, imgSize)
		+ CalcSimOfRect(region1, region2, imgSize));
}

void Segment::HisMerge(float* mergeHis
	, C_FLOAT* his1, C_FLOAT* his2
	, C_UINT32 hisSize
	, C_UINT32 region1Size, C_UINT32 region2Size)
{
	assert(mergeHis != nullptr);

	C_UINT32 mergeSize = region1Size + region2Size;

	for (UINT32 index = 0; index < hisSize; index++)
	{
		mergeHis[index] = static_cast<float>((his1[index] * region1Size + his2[index] * region2Size)) / mergeSize;
	}
}

void Segment::MergeRegions(Region& region, const Region &region1, const Region &region2
	, C_UINT32 label)
{
	region.rect = region1.rect | region2.rect;
	region.size = region1.size + region2.size;
	region.label = label;

	region.colorHist = new float[25 * 3];
	HisMerge(region.colorHist
		, region1.colorHist, region2.colorHist
		, 25 * 3
		, region1.size, region2.size);

	region.textureHist = new float[8 * 10 * 3];
	HisMerge(region.textureHist
		, region1.textureHist, region2.textureHist
		, 8 * 10 * 3
		, region1.size, region2.size);
}