#include "Library.h"
#include "Image.h"

Library::Library()
{

}

Library::~Library()
{
}

void Library::ChangeColor(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 type)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	switch (type)
	{
	case ColerType::BGR2GRAY_8BIT:
		BGR2Gray8Bit(src, pur, width, height);
		break;
	case ColerType::BGR2HSV:
		BGR2HSV(src, pur, width, height);
		break;
	case ColerType::HSV2BGR:
		HSV2BGR(src, pur, width, height);
		break;
	case ColerType::BGR2YCbCr:
		BGR2YCbCr(src, pur, width, height);
		break;
	case ColerType::YCbCr2BGR:
		YCbCr2BGR(src, pur, width, height);
		break;
	}
}

// 灰階
// R 0.299 ≈ 19595
// G 0.587 ≈ 38469
// B 0.114 ≈ 7472 (進位 反推回去比7471接近)
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void Library::BGR2Gray8Bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UCHAE* purEnd = pur + width * height + 1;

	while (pur < purEnd)
	{
		C_UINT32 B = *src;
		src++;

		C_UINT32 G = *src;
		src++;

		C_UINT32 R = *src;
		src++;

		C_UCHAE pix = static_cast<UCHAE>((R * 19595 + G * 38469 + B * 7472) >> 16);
		*pur = pix;
		pur++;
	}

}

void Library::BGR2HSV(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_DOUBLE B = *src;
		src++;

		C_DOUBLE G = *src;
		src++;

		C_DOUBLE R = *src;
		src++;

		double hsv[3];

		SetBGR2HSV(hsv, B, G, R);

		*pur = static_cast<UCHAE>(hsv[0]);
		pur++;
		*pur = static_cast<UCHAE>(hsv[1]);
		pur++;
		*pur = static_cast<UCHAE>(hsv[2]);
		pur++;
	}
}

void Library::SetBGR2HSV(double* const hsv
	, C_DOUBLE& B, C_DOUBLE& G, C_DOUBLE& R)
{

	C_DOUBLE max = std::max(std::max(R, G), B);
	C_DOUBLE min = std::min(std::min(R, G), B);

	*(hsv + 2) = max;

	C_DOUBLE difference = max - min;

	if (max != min)
	{
		if (max == R && G >= B)
		{
			*hsv = (G - B) / difference;
		}
		else if (max == R && G < B)
		{
			*hsv = (G - B) / difference + 6.0;
		}
		else if (max == G)
		{
			*hsv = (B - R) / difference + 2.0;
		}
		else if (max == B)
		{
			*hsv = (R - G) / difference + 4.0;
		}

		// 配合RGB正規化H和S
		*hsv *= 30.0;
		*(hsv + 1) = max == 0 ? 0 : (difference / max) * 255.0;
	}
}

void Library::HSV2BGR(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_DOUBLE H = static_cast<double>(*src);
		src++;

		C_DOUBLE S = static_cast<double>(*src);
		src++;

		C_DOUBLE V = static_cast<double>(*src);
		src++;

		double bgr[3];
		SetHSV2BGR(bgr, H, S, V);

		*pur = static_cast<UCHAE>(bgr[0]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[1]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[2]);
		pur++;
	}
}

void Library::SetHSV2BGR(double* const bgr
	, C_DOUBLE& H, C_DOUBLE& S, C_DOUBLE& V)
{
	C_DOUBLE fixH = H * 2.0;
	C_DOUBLE fixS = S / 255.0;

	C_UINT32 position = static_cast<int32_t>(fixH) / 60;
	C_DOUBLE offset = static_cast<int32_t>(fixH) % 60;

	// s = (max - min) / max，求min
	C_DOUBLE min = V * (1.0 - fixS);

	// -(f - 1) * (max - min) + min = g; 120.240.360
	C_DOUBLE q = -(offset - 60.0) * (V - min) / 60.0 + min;

	// f * (max - min) + min = g; 60.180.300
	C_DOUBLE t = offset * (V - min) / 60.0 + min;

	double R = 0;
	double G = 0;
	double B = 0;

	switch (position)
	{
	case 0:
		R = V;
		G = t;
		B = min;
		break;
	case 1:
		R = q;
		G = V;
		B = min;
		break;
	case 2:
		R = min;
		G = V;
		B = t;
		break;
	case 3:
		R = min;
		G = q;
		B = V;
		break;
	case 4:
		R = t;
		G = min;
		B = V;
		break;
	case 5:
		R = V;
		G = min;
		B = q;
		break;
	}
	*bgr = B;
	*(bgr + 1) = G;
	*(bgr + 2) = R;
}

void Library::AdjustmentHSV(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 H, C_INT32 S, C_INT32 V)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_DOUBLE B = static_cast<double>(*src);
		src++;

		C_DOUBLE G = static_cast<double>(*src);
		src++;

		C_DOUBLE R = static_cast<double>(*src);
		src++;

		double hsv[3];
		double bgr[3];

		SetBGR2HSV(hsv, B, G, R);

		if (H < 0)
		{
			hsv[0] = hsv[0] * static_cast<double>(100 + H) / 100.0;
		}
		else
		{
			hsv[0] = hsv[0] + (180 - hsv[0]) * static_cast<double>(H) / 100.0;
		}

		if (S < 0)
		{
			hsv[1] = hsv[1] * static_cast<double>(100.0 + S) / 100.0;
		}
		else
		{
			hsv[1] = hsv[1] + (255.0 - hsv[1]) * static_cast<double>(S) / 100.0;
		}

		if (V < 0)
		{
			hsv[2] = hsv[2] * static_cast<double>(100.0 + V) / 100.0;
		}
		else
		{
			hsv[2] = hsv[2] + (255.0 - hsv[2]) * static_cast<double>(V) / 100.0;
		}
		SetHSV2BGR(bgr, hsv[0], hsv[1], hsv[2]);

		*pur = static_cast<UCHAE>(bgr[0]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[1]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[2]);
		pur++;
	}
}

// BGR轉YCbCr
// Y = (66 * R + 129 * G + 25 * B + 128) >> 8 + 16
// Cb = (-38 * R - 74 * G + 112 * B + 128) >> 8 + 128
// Cr = (112 * R - 94 * G - 18 * B + 128) >> 8 + 128
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void Library::BGR2YCbCr(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_INT32 B = *src;
		src++;

		C_INT32 G = *src;
		src++;

		C_INT32 R = *src;
		src++;

		int32_t ycbcr[3];
		SetBGR2YCbCr(ycbcr, B, G, R);

		ycbcr[0] = (ycbcr[0] < 0 ? 0 : (ycbcr[0] > 255 ? 255 : ycbcr[0]));
		ycbcr[1] = (ycbcr[1] < 0 ? 0 : (ycbcr[1] > 255 ? 255 : ycbcr[1]));
		ycbcr[2] = (ycbcr[2] < 0 ? 0 : (ycbcr[2] > 255 ? 255 : ycbcr[2]));

		*pur = static_cast<UCHAE>(ycbcr[0]);
		pur++;
		*pur = static_cast<UCHAE>(ycbcr[1]);
		pur++;
		*pur = static_cast<UCHAE>(ycbcr[2]);
		pur++;
	}
}

void Library::SetBGR2YCbCr(int32_t* const ycbcr
	, C_INT32& B, C_INT32& G, C_INT32& R)
{
	*ycbcr = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
	*(ycbcr + 1) = ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128;
	*(ycbcr + 2) = ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128;
}

// YCbCr轉BGR
// R = (298 * (Y - 16) + 409 * (Cr - 128) + 128) >> 8
// G = (298 * (Y - 16) - 100 * (Cb - 128) - 208 * (Cr - 128) + 128) >> 8
// B = (298 * (Y - 16) + 516 * (Cr - 128) + 128) >> 8
// 為了快速運算(整數運算+位移) 先將數值左位移16次冪 65536
void Library::YCbCr2BGR(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_INT32 Y = *src;
		src++;

		C_INT32 Cb = *src;
		src++;

		C_INT32 Cr = *src;
		src++;

		int32_t bgr[3];
		SetYCbCr2BGR(bgr, Y, Cb, Cr);
		bgr[0] = (bgr[0] < 0 ? 0 : (bgr[0] > 255 ? 255 : bgr[0]));
		bgr[1] = (bgr[1] < 0 ? 0 : (bgr[1] > 255 ? 255 : bgr[1]));
		bgr[2] = (bgr[2] < 0 ? 0 : (bgr[2] > 255 ? 255 : bgr[2]));

		*pur = static_cast<UCHAE>(bgr[0]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[1]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[2]);
		pur++;
	}
}

void Library::SetYCbCr2BGR(int32_t* const bgr
	, C_INT32& Y, C_INT32& Cb, C_INT32& Cr)
{
	C_INT32 fixY = Y - 16;
	C_INT32 fixCb = Cb - 128;
	C_INT32 fixCr = Cr - 128;

	*bgr = (298 * fixY + 516 * fixCb + 128) >> 8;
	*(bgr + 1) = (298 * fixY - 100 * fixCb - 208 * fixCr + 128) >> 8;
	*(bgr + 2) = (298 * fixY + 409 * fixCr + 128) >> 8;
}

void Library::AdjustmentYCbCr(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 Y, C_INT32 Cb, C_INT32 Cr)
{
	C_UCHAE* purEnd = pur + width * 3 * height + 1;

	while (pur < purEnd)
	{
		C_INT32 B = *src;
		src++;

		C_INT32 G = *src;
		src++;

		C_INT32 R = *src;
		src++;

		int32_t ycbcr[3];
		int32_t bgr[3];

		SetBGR2YCbCr(ycbcr, B, G, R);

		if (Y < 0)
		{
			ycbcr[0] = static_cast<int32_t>(ycbcr[0] * static_cast<double>(100 + Y) / 100.0);
		}
		else
		{
			ycbcr[0] = static_cast<int32_t>(ycbcr[0] + (255 - ycbcr[0]) * static_cast<double>(Y) / 100.0);
		}

		if (Cb < 0)
		{
			ycbcr[1] = static_cast<int32_t>(ycbcr[1] * static_cast<double>(100 + Cb) / 100.0);
		}
		else
		{
			ycbcr[1] = static_cast<int32_t>(ycbcr[1] + (255 - ycbcr[1]) * static_cast<double>(Cb) / 100.0);
		}

		if (Cr < 0)
		{
			ycbcr[2] = static_cast<int32_t>(ycbcr[2] * static_cast<double>(100.0 + Cr) / 100.0);
		}
		else
		{
			ycbcr[2] = static_cast<int32_t>(ycbcr[2] + (255.0 - ycbcr[2]) * static_cast<double>(Cr) / 100.0);
		}

		SetYCbCr2BGR(bgr, ycbcr[0], ycbcr[1], ycbcr[2]);

		bgr[0] = (bgr[0] < 0 ? 0 : (bgr[0] > 255 ? 255 : bgr[0]));
		bgr[1] = (bgr[1] < 0 ? 0 : (bgr[1] > 255 ? 255 : bgr[1]));
		bgr[2] = (bgr[2] < 0 ? 0 : (bgr[2] > 255 ? 255 : bgr[2]));

		*pur = static_cast<UCHAE>(bgr[0]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[1]);
		pur++;
		*pur = static_cast<UCHAE>(bgr[2]);
		pur++;
	}
}

void Library::ImagePadding8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 pad)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);
	assert(pad >= 0);

	C_UINT32 copySize = width * sizeof(UCHAE);
	C_UINT32 purWidth = (width + 2 * pad);
	C_UCHAE* srcEnd = src + width * height;

	pur += (pad * purWidth) + pad;

	while (src < srcEnd)
	{
		memcpy(pur, src, copySize);
		pur += purWidth;
		src += width;
	}
}

void Library::Blur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	if (!(size & 1))
	{
		const_cast<UINT32&>(size) = size + 1;
	}

	C_UINT32 blockSize = size * size;
	C_INT32 pad = (size >> 1);
	C_UINT32 padWidth = width + pad * 2;
	C_UINT32 padHeight = height + pad * 2;
	UCHAE* padSrc = new UCHAE[padWidth * padWidth];

	ImagePadding8bit(src, padSrc, width, height, pad);

	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = pad; row < padHeight - pad; row++)
	{
		for (UINT32 col = pad; col < padWidth - pad; col++)
		{
			UINT32 sum = 0;

			for (int32_t blockRow = -pad; blockRow <= pad; blockRow++)
			{
				for (int32_t blockCol = -pad; blockCol <= pad; blockCol++)
				{
					sum += srcImage.image[row + blockRow][col + blockCol];
				}
			}
			purImage.image[row - pad][col - pad] = sum / blockSize;
		}
	}

	delete[] padSrc;
	padSrc = nullptr;
}

void Library::BlurGauss8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size, C_FLOAT sigma)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	if (!(size & 1))
	{
		const_cast<UINT32&>(size) = size + 1;
	}

	C_UINT32 blockSize = size * size;
	C_INT32 pad = (size >> 1);
	C_UINT32 padWidth = width + pad * 2;
	C_UINT32 padHeight = height + pad * 2;
	UCHAE* padSrc = new UCHAE[padWidth * padWidth];

	ImagePadding8bit(src, padSrc, width, height, pad);

	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	float** temp = new float*[size];

	for (UINT32 index = 0; index < size; index++)
	{
		temp[index] = new float[size];
	}

	Gaussian2DTemp(temp, size, sigma);


	for (UINT32 row = pad; row < padHeight - pad; row++)
	{
		for (UINT32 col = pad; col < padWidth - pad; col++)
		{
			float sum = 0;

			for (int32_t blockRow = -pad; blockRow <= pad; blockRow++)
			{
				for (int32_t blockCol = -pad; blockCol <= pad; blockCol++)
				{
					sum += (srcImage.image[row + blockRow][col + blockCol] * temp[pad + blockRow][pad + blockCol]);
				}
			}
			purImage.image[row - pad][col - pad] = static_cast<UCHAE>(sum);
		}
	}



	for (UINT32 index = 0; index < size; index++)
	{
		delete[] temp[index];
		temp[index] = nullptr;
	}
	delete[] temp;
	temp = nullptr;

	delete[] padSrc;
	padSrc = nullptr;
}

void Library::Gaussian2DTemp(float** const temp, C_INT32 size, C_FLOAT sigma)
{
	float sum = 0;
	C_INT32 center = size >> 1;
	C_FLOAT expBase = -(2.0f * sigma * sigma);
	C_FLOAT scaleBase = (2.0f * sigma * sigma) *  static_cast<float>(MNDT::PI);

	for (int32_t row = 0; row < size; row++)
	{
		C_INT32 y = center - row;
		for (int32_t col = 0; col < size; col++)
		{
			C_INT32 x = col - center;

			float gaussNum = 0;

			gaussNum = exp((x * x + y * y) / expBase);
			gaussNum = (gaussNum / scaleBase);
			temp[row][col] = gaussNum;
			sum += gaussNum;
		}
	}

	for (int32_t row = 0; row < size; row++)
	{
		for (int32_t col = 0; col < size; col++)
		{
			temp[row][col] /= sum;
		}
	}
}

void Library::MedianBlur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 size)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	if (!(size & 1))
	{
		const_cast<UINT32&>(size) = size + 1;
	}

	C_UINT32 blockSize = size * size;
	C_UINT32 medianBlockSize = blockSize >> 1;
	C_INT32 pad = (size >> 1);
	C_UINT32 padWidth = width + pad * 2;
	C_UINT32 padHeight = height + pad * 2;
	UCHAE* padSrc = new UCHAE[padWidth * padWidth];

	ImagePadding8bit(src, padSrc, width, height, pad);

	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);
	UCHAE* allPix = new UCHAE[blockSize];

	for (UINT32 row = pad; row < padHeight - pad; row++)
	{
		for (UINT32 col = pad; col < padWidth - pad; col++)
		{
			UINT32 index = 0;
			for (int32_t blockRow = -pad; blockRow <= pad; blockRow++)
			{
				for (int32_t blockCol = -pad; blockCol <= pad; blockCol++)
				{
					allPix[index++] = srcImage.image[row + blockRow][col + blockCol];
				}
			}
			std::sort(allPix, allPix + blockSize);
			purImage.image[row - pad][col - pad] = allPix[medianBlockSize];
		}
	}

	delete[] allPix;
	allPix = nullptr;

	delete[] padSrc;
	padSrc = nullptr;
}


void Library::BilateralBlur8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT spaceSigma, C_FLOAT colorSigma
	, C_UINT32 size)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	if (!(size & 1))
	{
		const_cast<UINT32&>(size) = size + 1;
	}

	C_UINT32 blockSize = size * size;
	C_INT32 pad = (size >> 1);
	C_UINT32 padWidth = width + pad * 2;
	C_UINT32 padHeight = height + pad * 2;
	UCHAE* padSrc = new UCHAE[padWidth * padWidth];

	ImagePadding8bit(src, padSrc, width, height, pad);

	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	C_FLOAT colorBase = -2.0f * colorSigma * colorSigma;
	C_FLOAT spaceBase = -2.0f * spaceSigma * spaceSigma;
	float* colorTemp = new float[256];
	float** spaceTemp = new float *[size];

	for (UINT32 index = 0; index < size; index++)
	{
		spaceTemp[index] = new float[size];
	}

	BilateralSpaceTemp(spaceTemp, size, spaceSigma);
	BilateralColorTemp(colorTemp, colorSigma);

	for (UINT32 row = pad; row < padHeight - pad; row++)
	{
		for (UINT32 col = pad; col < padWidth - pad; col++)
		{
			float sum = 0;
			float base = 0;
			C_CHAE& nowPix = srcImage.image[row][col];

			for (int32_t blockRow = -pad; blockRow <= pad; blockRow++)
			{
				for (int32_t blockCol = -pad; blockCol <= pad; blockCol++)
				{
					C_CHAE& blockPix = srcImage.image[row + blockRow][col + blockCol];
					C_UINT32 diff = abs(nowPix - blockPix);
					C_FLOAT num = colorTemp[diff] * spaceTemp[pad + blockRow][pad + blockCol];

					base += num;
					sum += (num * blockPix);
				}
			}
			purImage.image[row - pad][col - pad] = static_cast<UCHAE>(sum / base);
		}
	}


	for (UINT32 index = 0; index < size; index++)
	{
		delete[] spaceTemp[index];
		spaceTemp[index] = nullptr;
	}

	delete[] spaceTemp;
	spaceTemp = nullptr;

	delete[] colorTemp;
	colorTemp = nullptr;

	delete[] padSrc;
	padSrc = nullptr;
}


void Library::BilateralSpaceTemp(float** const temp, C_INT32 size, C_FLOAT sigma)
{
	C_INT32 pad = (size >> 1);
	C_FLOAT base = -2.0f * sigma * sigma;

	for (int32_t row = 0; row < size; row++)
	{
		C_INT32 y = pad - row;
		for (int32_t col = 0; col < size; col++)
		{
			C_INT32 x = col - pad;

			temp[row][col] = ((x * x) + (y * y)) / base;
		}
	}
}

void Library::BilateralColorTemp(float* const temp, C_FLOAT sigma)
{
	C_FLOAT base = -2.0f * sigma * sigma;

	for (int32_t index = 0; index < 256; index++)
	{
		temp[index] = exp((index * index) / base);
	}
}

void Library::Histogram8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	int32_t* histogram = new int32_t[256]{ 0 };
	int32_t max = 0;

	SetHistogram8bit(src, histogram, width, height);
	SetNormalizedHistogram8bit(histogram, 256, 255);


	Image purImage(pur, 256, 256, MNDT::GRAY_8BIT);

	for (UINT32 index = 0; index < 256; index++)
	{
		Point start(index, (255 - histogram[index]));
		Point end(index, 255);

		MNDT::DrawLine8bit(purImage, start, end);
	}

	delete[] histogram;
}

void Library::SetHistogram8bit(C_UCHAE* src, int32_t* histogram
	, C_UINT32 width, C_UINT32 height)
{
	C_UINT32 size = width * height;

	for (UINT32 count = 0; count < size; count++)
	{
		histogram[*src]++;
		src++;
	}
}

void Library::SetHistogram8bit(C_UCHAE* src, int32_t* histogram
	, C_UINT32 width, C_UINT32 height
	, C_UCHAE minRange, C_UCHAE maxRange
	, C_UCHAE bin)
{
	assert(maxRange > minRange);

	C_UCHAE diffRange = maxRange - minRange;
	C_UCHAE interval = diffRange / bin;
	C_UINT32 size = width * height;

	for (UINT32 count = 0; count < size; count++)
	{
		histogram[*(src + count) / interval]++;
	}
}

void Library::SetNormalizedHistogram8bit(int32_t* histogram
	, C_UINT32 size
	, C_UCHAE base)
{
	int32_t max = 0;

	for (UINT32 index = 0; index < size; index++)
	{
		max = max < histogram[index] ? histogram[index] : max;
	}


	float normalizedBase = static_cast<float>(base) / max;

	for (UINT32 index = 0; index < size; index++)
	{
		histogram[index] = static_cast<int32_t>(histogram[index] * normalizedBase);
	}
}

void Library::HistogramEqualization8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UINT32 size = width * height;
	int32_t* histogram = new int32_t[256]{ 0 };

	SetHistogram8bit(src, histogram, width, height);


	float base = 0;

	for (UINT32 index = 0; index < 256; index++)
	{
		if (histogram[index] > 0)
		{
			base += static_cast<float>(histogram[index]) / static_cast<float>(size);
			histogram[index] = static_cast<int32_t>(base * 255);
		}
	}

	for (UINT32 index = 0; index < size; index++)
	{
		*(pur + index) = histogram[*(src + index)];
	}

	delete[] histogram;
}

double Library::CompareHistogram(C_UCHAE* src, C_UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	int32_t* srcHistogram = new int32_t[256]{ 0 };
	int32_t* purHistogram = new int32_t[256]{ 0 };

	SetHistogram8bit(src, srcHistogram, width, height);
	SetHistogram8bit(pur, purHistogram, width, height);

	int32_t diff = 0;

	for (UINT32 index = 0; index < 256; index++)
	{
		diff += abs(srcHistogram[index] - purHistogram[index]);
	}

	return 1.0 - static_cast<double>(diff) / static_cast<double>(width * height);
}

void Library::Channel(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 channel)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);
	assert(channel > 0 && channel < 4);

	C_UCHAE* purEnd = pur + width * height + 1;

	src += (channel - 1);

	while (pur < purEnd)
	{
		*pur = *src;
		pur++;
		src += 3;
	}
}

void Library::BackProjection(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32* histogram
	, C_UCHAE minRange, C_UCHAE maxRange
	, C_UCHAE bin)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	C_UCHAE* purEnd = pur + width * height + 1;
	C_UCHAE diffRange = maxRange - minRange;
	C_UCHAE interval = diffRange / bin;


	while (pur < purEnd)
	{
		*pur = histogram[(*src) / interval];
		pur++;
		src++;
	}
}

//void Library::BackProjection(C_UCHAE* src, UCHAE* pur
//	, C_UINT32 srcWidth, C_UINT32 srcHeight
//	, C_UCHAE* hisSrc
//	, C_UINT32 hisWidth, C_UINT32 hisHeight
//	, C_UINT32 minRange, C_UINT32 maxRange
//	, C_UINT32 bin)
//{
//	assert(src != nullptr && pur != nullptr);
//	assert(srcWidth > 0 && srcHeight > 0);
//	assert(maxRange > minRange && minRange >= 0 && maxRange <= 256);
//	assert(bin > 0 && bin <= 256);
//
//	int32_t* histogram = new int32_t[bin]{ 0 };
//
//	SetHistogram8bit(hisSrc, histogram
//		, hisWidth, hisHeight
//		, minRange, maxRange
//		, bin);
//
//	SetNormalizedHistogram8bit(histogram
//		, bin
//		, maxRange);
//
//
//	C_UCHAE* purEnd = pur + srcWidth * srcHeight + 1;
//	C_UCHAE diffRange = maxRange - minRange;
//	C_UCHAE interval = diffRange / bin;
//
//
//	while (pur < purEnd)
//	{
//		*pur = histogram[(*src) / interval];
//		pur++;
//		src++;
//	}
//}

void Library::MeanShift(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32* rectPoint
	, C_UINT32 times
	, C_DOUBLE threshold)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	memcpy(pur, src, width * height * sizeof(UCHAE));

	Image srcImage(const_cast<UCHAE*>(src), width, height, ColerType::BGR2GRAY_8BIT);
	Image purImage(const_cast<UCHAE*>(pur), width, height, ColerType::BGR2GRAY_8BIT);
	Rect rect(rectPoint[0], rectPoint[1], rectPoint[2], rectPoint[3]);

	MNDT::DrawRect8bit(purImage, rect);

	for (UINT32 time = 0; time < times; time++)
	{
		C_UINT32 endX = rect.EndX();
		C_UINT32 endY = rect.EndY();

		int32_t centerX = (rect.Width() >> 1) + rect.X();
		int32_t centerY = (rect.Height() >> 1) + rect.Y();
		int32_t sumX = 0;
		int32_t sumY = 0;
		int32_t sumBase = 0;

		for (UINT32 y = rect.Y(); y < endY; y++)
		{
			for (UINT32 x = rect.X(); x < endX; x++)
			{
				if (srcImage.image[y][x] > 0)
				{
					C_INT32 xDiff = x - centerX;
					C_INT32 yDiff = y - centerY;

					sumX += (xDiff * srcImage.image[y][x]);
					sumY += (yDiff * srcImage.image[y][x]);
					sumBase += srcImage.image[y][x];
				}
			}
		}

		C_DOUBLE offsetX = (static_cast<double>(sumX) / static_cast<double>(sumBase));
		C_DOUBLE offsetY = (static_cast<double>(sumY) / static_cast<double>(sumBase));
		int32_t updateX = rect.X() + static_cast<int32_t>(offsetX);
		int32_t updateY = rect.Y() + static_cast<int32_t>(offsetY);

		updateX = std::min(std::max(updateX, 0), static_cast<int32_t>(width - 1));
		updateY = std::min(std::max(updateY, 0), static_cast<int32_t>(height - 1));

		rect.X(updateX);
		rect.Y(updateY);

		// loss
		if ((offsetX * offsetX + offsetY * offsetY) <= threshold) break;
	}

	MNDT::DrawRect8bit(purImage, rect);
}

void Library::Threshold8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 thresh)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	C_UCHAE* purEnd = pur + width * height + 1;

	while (pur < purEnd)
	{
		if (*src < thresh)
		{
			*pur = 0;
		}
		else
		{
			*pur = 255;
		}
		pur++;
		src++;
	}
}