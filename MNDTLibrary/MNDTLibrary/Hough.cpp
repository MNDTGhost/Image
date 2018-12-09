#include "Hough.h"

namespace MNDT {
	//void HoughLines(C_UCHAR* src, UCHAR* pur
	//	, C_UINT32 width, C_UINT32 height
	//	, C_FLOAT rho, C_FLOAT theta, C_FLOAT threshold)
	//{
	//	C_FLOAT fixRho = 1.0f / rho;
	//	C_UINT32 thetaSize = static_cast<UINT32>(PI / theta);
	//	float* fixSin = new float[thetaSize];
	//	float* fixCos = new float[thetaSize];
	//
	//	for (UINT32 index = 0; index < thetaSize; index++)
	//	{
	//		fixSin[index] = FixValue(sin(theta * index)) * fixRho;
	//		fixCos[index] = FixValue(cos(theta * index)) * fixRho;
	//	}
	//
	//	Image srcImage(const_cast<UCHAR*>(src), width, height, ImageType::GRAY_8BIT);
	//	C_DOUBLE originalR = std::max((width + height) * sin(PI / 4.0), static_cast<double>(std::max(width, height)));
	//	//C_DOUBLE originalR = 14 * sin(PI / 4.0);
	//	C_UINT32 maxR = static_cast<UINT32>(originalR * fixRho) + 1 + 2;
	//	C_UINT32 xAxisOffset = maxR * (thetaSize + 2);
	//	UINT32* count = new UINT32[xAxisOffset * 2]{ 0 };
	//
	//	for (UINT32 row = 0; row < height; row++)
	//	{
	//		for (UINT32 col = 0; col < width; col++)
	//		{
	//			if (srcImage.image[row][col] > 0)
	//			{
	//				for (UINT32 index = 0; index < thetaSize; index++)
	//				{
	//					int32_t r = static_cast<int32_t>(fixSin[index] * row + fixCos[index] * col);
	//
	//					r = r < 0 ? abs(r) + xAxisOffset : r;
	//					count[maxR * (index + 1) + r + 1]++;
	//				}
	//			}
	//		}
	//	}
	//
	//
	//	//for (UINT32 index = 0; index < thetaSize; index++)
	//	//{
	//	//	int32_t r = static_cast<int32_t>(fixSin[index] * 7 + fixCos[index] * 7);
	//	//	UINT32 offset = r < 0 ? xAxisOffset : 0;
	//	//	count[offset + abs(r) + maxR * index]++;
	//
	//	//	r = static_cast<int32_t>(fixSin[index] * 3 + fixCos[index] * 3);
	//	//	offset = r < 0 ? xAxisOffset : 0;
	//	//	count[offset + abs(r) + maxR * index]++;
	//
	//	//	r = static_cast<int32_t>(fixSin[index] * 5 + fixCos[index] * 5);
	//	//	offset = r < 0 ? xAxisOffset : 0;
	//	//	count[offset + abs(r) + maxR * index]++;
	//
	//	//	r = static_cast<int32_t>(fixSin[index] * 1 + fixCos[index] * 1);
	//	//	offset = r < 0 ? xAxisOffset : 0;
	//	//	count[offset + abs(r) + maxR * index]++;
	//
	//	//}
	//
	//	//SetNormalizedHistogram8bit(count, maxR * thetaSize * 2, 255);
	//
	//	//HoughDrawPolar(pur
	//	//	, width, height
	//	//	, count
	//	//	, theta, maxR);
	//
	//	UINT32* findCount = new UINT32[xAxisOffset * 2]{ 0 };
	//	UINT32 findIndex = 0;
	//
	//	for (UINT32 index = 0; index < thetaSize; index++)
	//	{
	//		C_UINT32 offset = maxR * (index + 1);
	//		UINT32* nowCountPointer = nullptr;
	//
	//		for (UINT32 countIndex = offset + 1; countIndex < offset + maxR - 1; countIndex++)
	//		{
	//			// +
	//			nowCountPointer = count + countIndex;
	//			if (*nowCountPointer > threshold
	//				|| *nowCountPointer > *(nowCountPointer - 1)
	//				|| *nowCountPointer > *(nowCountPointer + 1)
	//				|| *nowCountPointer > *(nowCountPointer - maxR)
	//				|| *nowCountPointer > *(nowCountPointer + maxR))
	//			{
	//				findCount[findIndex++] = countIndex;
	//			}
	//
	//			// -
	//			nowCountPointer = count + countIndex + xAxisOffset;
	//
	//			if (*nowCountPointer > threshold
	//				|| *nowCountPointer > *(nowCountPointer - 1)
	//				|| *nowCountPointer > *(nowCountPointer + 1)
	//				|| *nowCountPointer > *(nowCountPointer - maxR)
	//				|| *nowCountPointer > *(nowCountPointer + maxR))
	//			{
	//				findCount[findIndex++] = countIndex + xAxisOffset;
	//			}
	//		}
	//	}
	//
	//	std::sort(findCount, findCount + findIndex
	//		, [&count](const UINT32& index1, const UINT32& index2) { return *(count + index1) > *(count + index2); });
	//
	//	Image purImage(pur, width, height, ImageType::GRAY_8BIT);
	//
	//	for (UINT32 index = 0; index < findIndex; index++)
	//	{
	//		UINT32 countIndex = findCount[index] - 1;
	//		
	//		if (countIndex < xAxisOffset)
	//		{
	//			UINT32 thetaIndex = countIndex / maxR - 1;
	//			int32_t r = countIndex % maxR;
	//			float dangle = theta * thetaIndex;
	//			float drho =  r;
	//
	//			double a = cos(dangle), b = sin(dangle);
	//			double x0 = a*drho , y0 = b*drho ;
	//			int32_t x1 = x0 - 1*b;
	//			int32_t y1 = y0 + 1* a ;
	//			int32_t x2 = x0 + 1* b;
	//			int32_t y2 = y0 - 1* a ;
	//
	//			if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0
	//				|| x1 >= width || y1 >= height || x2 >= width || y2 >= height)
	//			{
	//				continue;
	//			}
	//			DrawLine8bit(purImage, Point(x1, y1), Point(x2, y2));
	//		}
	//		else
	//		{
	//			countIndex -= xAxisOffset;
	//			UINT32 thetaIndex = countIndex / maxR - 1;
	//			int32_t r = countIndex % maxR;
	//			float dangle = theta * thetaIndex;
	//			float drho = -r;
	//
	//			double a = cos(dangle), b = sin(dangle);
	//			double x0 = a*drho, y0 = b*drho;
	//			int32_t x1 = x0 - b;
	//			int32_t y1 = y0 + a;
	//			int32_t x2 = x0 + b;
	//			int32_t y2 = y0 - a;
	//
	//			if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0
	//				|| x1 >= width || y1 >= height || x2 >= width || y2 >= height)
	//			{
	//				continue;
	//			}
	//			DrawLine8bit(purImage, Point(x1, y1), Point(x2, y2));
	//		}
	//
	//		//int32_t r = static_cast<int32_t>(rho(fixSin[index] * row + fixCos[index] * col));
	//
	//		//r = r < 0 ? abs(r) + xAxisOffset : r;
	//		//count[maxR * (index + 1) + r + 1]++;
	//	}
	//
	//	//for (UINT32 row = 0; row < height; row++)
	//	//{
	//	//	for (UINT32 col = 0; col < width; col++)
	//	//	{
	//	//		if (srcImage.image[row][col] > 0)
	//	//		{
	//	//			for (UINT32 index = 0; index < thetaSize; index++)
	//	//			{
	//	//				int32_t r = static_cast<int32_t>(fixSin[index] * row + fixCos[index] * col);
	//
	//	//				r = r < 0 ? abs(r) + xAxisOffset : r;
	//	//				if (count[maxR * (index + 1) + r + 1] > 0)
	//	//				{
	//	//					purImage.image[row][col] = 150;
	//	//					break;
	//	//				}
	//	//			}
	//	//		}
	//	//	}
	//	//}
	//
	//	delete[] findCount;
	//	findCount = nullptr;
	//
	//	delete[] fixSin;
	//	fixSin = nullptr;
	//
	//	delete[] fixCos;
	//	fixCos = nullptr;
	//
	//	delete[] count;
	//	count = nullptr;
	//}
	void HoughLines(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT rho, C_FLOAT theta, C_UINT32 threshold)
	{
		// 1. init params
		C_FLOAT fixRho = 1.0f / rho;
		C_UINT32 thetaSize = static_cast<UINT32>(PI / theta);
		float* fixSin = new float[thetaSize];
		float* fixCos = new float[thetaSize];

		for (UINT32 index = 0; index < thetaSize; index++)
		{
			fixSin[index] = FixValue(sin(theta * index)) * fixRho;
			fixCos[index] = FixValue(cos(theta * index)) * fixRho;
		}

		// 2. hough total
		Image srcImage(const_cast<UCHAR*>(src), width, height, ImageType::GRAY_8BIT);
		C_DOUBLE originalR = std::max((width + height) * sin(PI / 4.0), static_cast<double>(std::max(width, height)));
		C_UINT32 maxR = static_cast<UINT32>(originalR * fixRho) + 1 + 2;
		C_UINT32 xAxisOffset = maxR * (thetaSize + 2);
		UINT32* count = new UINT32[xAxisOffset * 2]{ 0 };

		for (UINT32 row = 0; row < height; row++)
		{
			for (UINT32 col = 0; col < width; col++)
			{
				if (srcImage.image[row][col] > 0)
				{
					for (UINT32 index = 0; index < thetaSize; index++)
					{
						int32_t r = static_cast<int32_t>(fixSin[index] * row + fixCos[index] * col);

						r = r < 0 ? abs(r) + xAxisOffset : r;
						count[maxR * (index + 1) + r + 1]++;
					}
				}
			}
		}

		//// draw hough
		//Inner::DrawHoughPolar(pur
		//	, width, height
		//	, count
		//	, theta, maxR);

		// 3. update neighbours
		Inner::HoughLineNeighboursUpdate(count
			, thetaSize, maxR
			, threshold);


		// 4. draw line
		Image purImage(pur, width, height, ImageType::GRAY_8BIT);

		for (UINT32 row = 0; row < height; row++)
		{
			for (UINT32 col = 0; col < width; col++)
			{
				if (srcImage.image[row][col] > 0)
				{
					for (UINT32 index = 0; index < thetaSize; index++)
					{
						int32_t r = static_cast<int32_t>(fixSin[index] * row + fixCos[index] * col);

						r = r < 0 ? abs(r) + xAxisOffset : r;
						if (count[maxR * (index + 1) + r + 1] > 0)
						{
							purImage.image[row][col] = 255;
						}
					}
				}
			}
		}

		delete[] fixSin;
		fixSin = nullptr;

		delete[] fixCos;
		fixCos = nullptr;

		delete[] count;
		count = nullptr;
	}

	void Inner::DrawHoughPolar(UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_UINT32* count
		, C_FLOAT theta, C_UINT32 maxR)
	{
		C_UINT32 thetaSize = static_cast<UINT32>(PI / theta);
		C_UINT32 xAxisOffset = maxR * (thetaSize + 2);
		C_UINT32 halfHeight = height >> 1;
		Image purImage(pur, width, height, ImageType::GRAY_8BIT);

		for (UINT32 index = 0; index < thetaSize; index++)
		{
			C_UINT32 x = static_cast<UINT32>(theta * index / PI * width);
			C_UINT32 offset = maxR * (index + 1);

			for (UINT32 countIndex = offset + 1; countIndex < offset + maxR; countIndex++)
			{
				// x axis -> + and -
				for (UINT32 axis = 0; axis < 2; axis++)
				{
					C_UINT32* nowCountPointer = count + countIndex + xAxisOffset * axis;

					if (*nowCountPointer > 0)
					{
						C_UINT32 y = static_cast<UINT32>(halfHeight + (countIndex - offset) / static_cast<float>(maxR) * halfHeight);
						Point point(x, y);

						DrawPoint8bit(purImage, point);
					}
				}
			}
		}
	}

	void Inner::HoughLineNeighboursUpdate(UINT32* count
		, C_UINT32 thetaSize, C_UINT32 maxR
		, C_UINT32 threshold)
	{
		C_UINT32 xAxisOffset = maxR * (thetaSize + 2);

		for (UINT32 index = 0; index < thetaSize; index++)
		{
			C_UINT32 offset = maxR * (index + 1);

			for (UINT32 countIndex = offset + 1; countIndex < offset + maxR - 1; countIndex++)
			{
				// x axis -> + and -
				for (UINT32 axis = 0; axis < 2; axis++)
				{
					UINT32* nowCountPointer = count + countIndex + xAxisOffset * axis;

					if (*nowCountPointer < threshold
						|| *nowCountPointer < *(nowCountPointer - 1)
						|| *nowCountPointer < *(nowCountPointer + 1)
						|| *nowCountPointer < *(nowCountPointer - maxR)
						|| *nowCountPointer < *(nowCountPointer + maxR))
					{
						*nowCountPointer = 0;
					}
				}

			}
		}
	}


	void HoughCircles(C_UCHAR* src, UCHAR* pur
		, C_UINT32 width, C_UINT32 height
		, C_FLOAT minRadius, C_FLOAT maxRadius, C_UINT32 threshold)
	{
		// 1. total
		UINT32* count = new UINT32[(width + 2) * (height + 2)]{ 0 };

		Inner::HoughCirclesCount(src
			, width, height
			, count
			, minRadius, maxRadius);


		// 2. update neighbours
		Inner::HoughCircleNeighboursUpdate(count
			, width, height
			, threshold);

		// 3. draw
		Image srcImage(const_cast<UCHAR*>(src), width, height, ImageType::GRAY_8BIT);
		Image purImage(pur, width, height, ImageType::GRAY_8BIT);

		for (UINT32 row = 0; row < height; row++)
		{
			C_UINT32 rowIndex = (row + 1) * width;

			for (UINT32 col = 0; col < width; col++)
			{
				C_UINT32 nowIndex = rowIndex + col + 1;

				if (count[nowIndex] == 0)
				{
					continue;
				}

				for (float radius = minRadius; radius <= maxRadius; radius++)
				{
					bool nCircle = false;

					for (float pi = 0; pi <= PI * 2; pi += 0.2f)
					{
						int32_t y = static_cast<int32_t>(static_cast<float>(row) + FixValue(sin(pi)) * radius);
						int32_t x = static_cast<int32_t>(static_cast<float>(col) + FixValue(cos(pi)) * radius);

						if (x < 0 || y < 0
							|| (unsigned)x >= width || (unsigned)y >= height
							|| srcImage.image[y][x] == 0)
						{
							nCircle = true;
							break;
						}
					}

					if (nCircle)
					{
						continue;
					}

					for (float pi = 0; pi <= PI * 2; pi += 0.2f)
					{
						C_UINT32 y = static_cast<UINT32>(row + FixValue(sin(pi)) * radius);
						C_UINT32 x = static_cast<UINT32>(col + FixValue(cos(pi)) * radius);

						purImage.image[y][x] = 255;
					}
				}
			}
		}

		delete[] count;
		count = nullptr;
	}

	void Inner::HoughCirclesCount(C_UCHAR* src
		, C_UINT32 width, C_UINT32 height
		, UINT32* count
		, C_FLOAT minRadius, C_FLOAT maxRadius)
	{
		assert(count != nullptr);

		// get gradient
		int32_t* Gx = new int32_t[width * height];
		int32_t* Gy = new int32_t[width * height];

		Sobel8bit(src, Gx
			, width, height
			, true, false);

		Sobel8bit(src, Gy
			, width, height
			, false, true);

		// calculate gradient total
		Image srcImage(const_cast<UCHAR*>(src), width, height, ImageType::GRAY_8BIT);

		for (UINT32 row = 0; row < height; row++)
		{
			C_UINT32 rowIndex = row * width;

			for (UINT32 col = 0; col < width; col++)
			{
				C_UINT32 index = rowIndex + col;

				if (srcImage.image[row][col] > 0)
				{
					C_FLOAT magnitude = static_cast<float>(sqrt(Gx[index] * Gx[index] + Gy[index] * Gy[index] + 0.0001f));
					float offsetX = Gx[index] / magnitude;
					float offsetY = Gy[index] / magnitude;

					for (UINT32 sign = 0; sign < 2; sign++)
					{
						float x = col + minRadius * offsetX;
						float y = row + minRadius * offsetY;

						for (float radius = minRadius; radius <= maxRadius; radius++)
						{
							if (x < 0 || y < 0
								|| x >= width || y >= height)
							{
								continue;
							}
							//DrawLine8bit(purImage, Point(col, row), Point(static_cast<UINT32>(x), static_cast<UINT32>(y)));
							HoughCirclePointCount(count, width, Point(col, row), Point(static_cast<UINT32>(x), static_cast<UINT32>(y)));
							x += offsetX;
							y += offsetY;
						}

						offsetX = -offsetX;
						offsetY = -offsetY;
					}
				}
			}
		}

		delete[] Gx;
		Gx = nullptr;

		delete[] Gy;
		Gy = nullptr;
	}

	void Inner::HoughCirclePointCount(UINT32* count
		, C_UINT32 width
		, const Point& p1, const Point& p2)
	{
		C_UINT32 absDiffX = abs(static_cast<int32_t>(p1.X()) - static_cast<int32_t>(p2.X()));
		C_UINT32 absDiffY = abs(static_cast<int32_t>(p1.Y()) - static_cast<int32_t>(p2.Y()));
		C_UINT32 base = absDiffX > absDiffY ? absDiffY : absDiffX;
		C_INT32 diffX = static_cast<int32_t>(p1.X()) - static_cast<int32_t>(p2.X());
		C_INT32 diffY = static_cast<int32_t>(p1.Y()) - static_cast<int32_t>(p2.Y());
		C_INT32 baseX = diffX < 0 ? 1 : -1;
		C_INT32 baseY = diffY < 0 ? 1 : -1;

		int32_t x = p1.X();
		int32_t y = p1.Y();

		for (UINT32 index = 0; index < base; index++)
		{
			count[static_cast<UINT32>(static_cast<UINT32>(y + 1) * width + x + 1)]++;
			x += baseX;
			y += baseY;
		}
	}


	void Inner::HoughCircleNeighboursUpdate(UINT32* count
		, C_UINT32 width, C_UINT32 height
		, C_UINT32 threshold)
	{
		// 4¾F¤ñ¸û
		for (UINT32 row = 0; row < height; row++)
		{
			C_UINT32 rowIndex = (row + 1) * width;

			for (UINT32 col = 0; col < width; col++)
			{
				C_UINT32 nowIndex = rowIndex + col + 1;
				UINT32* nowCountPointer = count + nowIndex;

				if (*nowCountPointer < threshold
					|| *nowCountPointer < *(nowCountPointer - 1)
					|| *nowCountPointer < *(nowCountPointer + 1)
					|| *nowCountPointer < *(nowCountPointer - width - 2)
					|| *nowCountPointer < *(nowCountPointer + width + 2))
				{
					*nowCountPointer = 0;
				}
			}
		}
	}
}