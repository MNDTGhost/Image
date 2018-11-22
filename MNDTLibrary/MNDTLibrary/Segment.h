#pragma once
#ifndef SEGMENT_H
#define SEGMENT_H
#include "Library.h"
#include "GraphTree.h"

typedef std::pair<UINT32, UINT32> Neighbour;

typedef struct {
	UINT32 centerIndex;
	UINT32 linkIndex;
	double weights;
} Edge;

struct Region {
	UINT32 size;
	UINT32 label;
	Rect rect;
	float* colorHist;
	float* textureHist;

	Region()
	{
		Region::size = 0;
		Region::rect = Rect(INT_MAX, INT_MAX, 0, 0);
		Region::label = 0;
		Region::colorHist = nullptr;
		Region::textureHist = nullptr;
	}

	Region(C_UINT32 label)
	{
		Region::size = 1;
		Region::rect = Rect(INT_MAX, INT_MAX, 0, 0);
		Region::label = label;
		Region::colorHist = nullptr;
		Region::textureHist = nullptr;
	}

	~Region()
	{
		if (colorHist != nullptr)
		{
			delete[] colorHist;
			colorHist = nullptr;
		}

		if (textureHist != nullptr)
		{
			delete[] textureHist;
			textureHist = nullptr;
		}
	}
	//Region(C_UINT32 size
	//	, C_UINT32 label
	//	, const Rect rect
	//	, float* colorHist, float* textureHist)
	//{
	//	Region::size = size;
	//	Region::rect = rect;
	//	Region::label = label;
	//	Region::colorHist = colorHist;
	//	Region::textureHist = textureHist;
	//}

};


// hash
namespace std
{
	template<>
	class hash<Neighbour>
	{
	public:
		std::size_t operator()(const Neighbour &data) const
		{
			return hash<UINT32>()(data.first) ^ hash<UINT32>()(data.second);
		}
	};
}


class Segment {
public:

	inline Pixel GetColor()
	{
		return Pixel(rand() % 255, rand() % 255, rand() % 255);
	}

	inline float Diff(const Pixel& pix1, const Pixel& pix2)
	{
		return static_cast<float>(sqrt(pow(pix1.B - pix2.B, 2) +
			pow(pix1.B - pix2.B, 2) +
			pow(pix1.B - pix2.B, 2)));
	}

	inline double Threshold(C_FLOAT& threshold, C_FLOAT& size)
	{
		return threshold / size;
	}

	void SegmentImage(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize
		, GraphTree* graphTree);

	void Visualization(Image& image
		, GraphTree* graphTree);

	void SelectiveSearch(C_UCHAE* src, UCHAE* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT sigma, C_FLOAT threshold, C_UINT32 minSize);
private:
	void SegmentGraph(GraphTree* graphTree
		, Edge* edges, C_UINT32 edgeSize
		, C_FLOAT threshold);

	void CalcSize(const Image& image
		, Region& region
		, GraphTree* graphTree);

	void CalcTextureGradient(const Image& image, float* angle);

	void CalcColourHist(const Image& hsv
		, Region& region
		, GraphTree* graphTree);

	void CalcTextureHist(const Image& image
		, C_FLOAT* angle
		, Region& region
		, GraphTree* graphTree);

	std::map<UINT32, Region>ExtractRegion(const Image& image
		, GraphTree* graphTree);

	inline bool Intersecting(const Region &region1, const Region &region2) const;

	std::vector<Neighbour>ExtractNeighbours(const std::map<UINT32, Region>& R);

	double CalcSimOfColor(const Region &region1, const Region &region2);

	double CalcSimOfTexture(const Region &region1, const Region &region2);

	inline double CalcSimOfSize(const Region &region1, const Region &region2
		, C_UINT32 imgSize);

	inline double CalcSimOfRect(const Region &region1, const Region &region2
		, C_UINT32 imgSize);

	inline double CalcSimilarity(const Region &region1, const Region &region2
		, C_UINT32 imgSize);

	void HisMerge(float* mergeHis
		, C_FLOAT* his1, C_FLOAT* his2
		, C_UINT32 hisSize
		, C_UINT32 region1Size, C_UINT32 region2Size);

	void MergeRegions(Region& region, const Region &region1, const Region &region2
		, C_UINT32 label);
};

#endif