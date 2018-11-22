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
	C_UCHAE* purEnd = pur + width * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UCHAE* purEnd = pur + width * 3 * height;

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
	C_UINT32 purWidth = (width + (pad << 1));
	C_UCHAE* srcEnd = src + width * height;

	pur += (pad * purWidth) + pad;

	while (src < srcEnd)
	{
		memcpy(pur, src, copySize);
		pur += purWidth;
		src += width;
	}
}

void Library::ImagePadding24bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_INT32 pad)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);
	assert(pad >= 0);

	C_UINT32 copySize = width * 3 * sizeof(UCHAE);
	C_UINT32 purWidth = (width + 2 * pad) * 3;
	C_UINT32 srcWidth = width * 3;
	C_UCHAE* srcEnd = src + width * height * 3;

	pur += (pad * purWidth) + pad * 3;

	while (src < srcEnd)
	{
		memcpy(pur, src, copySize);
		pur += purWidth;
		src += srcWidth;
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
	C_UINT32 padWidth = width + (pad << 1);
	C_UINT32 padHeight = height + (pad << 1);
	UCHAE* padSrc = new UCHAE[padWidth * padHeight];

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
	C_UINT32 padWidth = width + (pad << 1);
	C_UINT32 padHeight = height + (pad << 1);
	UCHAE* padSrc = new UCHAE[padWidth * padHeight];

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

void Library::BlurGauss24bit(C_UCHAE* src, UCHAE* pur
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
	C_UINT32 padWidth = width + (pad << 1);
	C_UINT32 padHeight = height + (pad << 1);
	UCHAE* padSrc = new UCHAE[padWidth * padHeight * 3];

	ImagePadding24bit(src, padSrc, width, height, pad);

	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::BGR_24BIT);
	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);

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
			float bSum = 0;
			float gSum = 0;
			float rSum = 0;

			for (int32_t blockRow = -pad; blockRow <= pad; blockRow++)
			{
				for (int32_t blockCol = -pad; blockCol <= pad; blockCol++)
				{
					float base = temp[pad + blockRow][pad + blockCol];
					Pixel pix = srcImage.GetPixel(row + blockRow, col + blockCol);

					bSum += (pix.B * base);
					gSum += (pix.G * base);
					rSum += (pix.R * base);
				}
			}
			Pixel pix(static_cast<UCHAE>(bSum), static_cast<UCHAE>(gSum), static_cast<UCHAE>(rSum));

			purImage.SetPixel(row - pad, col - pad, pix);
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
	C_UINT32 padWidth = width + (pad << 1);
	C_UINT32 padHeight = height + (pad << 1);
	UCHAE* padSrc = new UCHAE[padWidth * padHeight];

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
	C_UINT32 padWidth = width + (pad << 1);
	C_UINT32 padHeight = height + (pad << 1);
	UCHAE* padSrc = new UCHAE[padWidth * padHeight];

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
		histogram[(*(src + count) / interval) % bin]++;
	}
}

void Library::SetNormalizedHistogram8bit(float* histogram
	, C_UINT32 size
	, MNDT::Normalized type)
{
	switch (type)
	{
	case MNDT::L1:
		L1NormalizedHistogram8bit(histogram, size);
		break;
	case MNDT::L2:
		L2NormalizedHistogram8bit(histogram, size);
		break;
	}
}

void Library::L1NormalizedHistogram8bit(float* histogram
	, C_UINT32 size)
{
	float L1 = 0;

	for (UINT32 index = 0; index < size; index++)
	{
		L1 += histogram[index];
	}


	for (UINT32 index = 0; index < size; index++)
	{
		histogram[index] /= L1;
	}
}

void Library::L2NormalizedHistogram8bit(float* histogram
	, C_UINT32 size)
{
	float L2 = 0.0f;

	for (UINT32 index = 0; index < size; index++)
	{
		L2 += (histogram[index] * histogram[index]);
	}

	L2 = sqrt(L2 + 0.000001f);

	for (UINT32 index = 0; index < size; index++)
	{
		histogram[index] /= L2;
	}
}

// L1 Norm
void Library::SetNormalizedHistogram24bit(float* histogram
	, C_UINT32 size)
{
	float L1[3] = { 0, 0, 0 };

	for (UINT32 index = 0; index < size; index++)
	{
		L1[0] += histogram[index];
		L1[1] += histogram[index + size];
		L1[2] += histogram[index + size + size];
	}


	for (UINT32 index = 0; index < size; index++)
	{
		histogram[index] /= L1[0];
		histogram[index + size] /= L1[1];
		histogram[index + size + size] /= L1[2];
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

	C_UCHAE* purEnd = pur + width * height;

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

	C_UCHAE* purEnd = pur + width * height;
	C_UCHAE diffRange = maxRange - minRange;
	C_UCHAE interval = diffRange / bin;


	while (pur < purEnd)
	{
		*pur = histogram[((*src) / interval) % bin];
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
//	C_UCHAE* purEnd = pur + srcWidth * srcHeight;
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

	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(const_cast<UCHAE*>(pur), width, height, MNDT::ImageType::GRAY_8BIT);
	Rect rect(rectPoint[0], rectPoint[1], rectPoint[2], rectPoint[3]);

	MNDT::DrawRect8bit(purImage, rect);

	for (UINT32 time = 0; time < times; time++)
	{
		C_UINT32 endX = rect.EndX() + 1;
		C_UINT32 endY = rect.EndY() + 1;

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

void Library::Rotate8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, MNDT::RotateType type)
{
	switch (type)
	{
	case MNDT::RotateType::HORIZONTAL:
		RotateHorizontal8bit(src, pur
			, width, height);
		break;
	case MNDT::RotateType::VERTICAL:
		RotateVertical8bit(src, pur
			, width, height);
		break;
	}
}

void Library::RotateHorizontal8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = 0; row < height; row++)
	{
		UINT32 purIndex = 0;

		for (int32_t col = width - 1; col >= 0; col--)
		{
			purImage.image[row][purIndex] = srcImage.image[row][col];
			purIndex++;
		}
	}
}

void Library::RotateVertical8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);
	C_UINT32 copySize = width * sizeof(UCHAE);
	UINT32 purIndex = 0;

	for (int32_t row = height - 1; row >= 0; row--)
	{
		memcpy(purImage.image[purIndex], srcImage.image[row], copySize);
		purIndex++;
	}
}

void Library::Resize8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 reWidth, C_UINT32 reHeight
	, MNDT::ResizeType type)
{
	switch (type)
	{
	case MNDT::ResizeType::NEAREST:
		NearestResize8bit(src, pur
			, width, height
			, reWidth, reHeight);
		break;
	case MNDT::ResizeType::LINEAR:
		LinearResize8bit(src, pur
			, width, height
			, reWidth, reHeight);
		break;
	}
}

void Library::NearestResize8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 reWidth, C_UINT32 reHeight)
{
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, reWidth, reHeight, MNDT::ImageType::GRAY_8BIT);

	float xBase = static_cast<float>(width - 1) / static_cast<float>(reWidth - 1);
	float yBase = static_cast<float>(height - 1) / static_cast<float>(reHeight - 1);

	for (UINT32 row = 0; row < reHeight; row++)
	{
		C_UINT32 srcRow = static_cast<UINT32>(row * yBase);

		for (UINT32 col = 0; col < reWidth; col++)
		{
			C_UINT32 srcCol = static_cast<UINT32>(col * xBase);

			purImage.image[row][col] = srcImage.image[srcRow][srcCol];
		}
	}
}

void Library::LinearResize8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 reWidth, C_UINT32 reHeight)
{
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, reWidth, reHeight, MNDT::ImageType::GRAY_8BIT);

	C_FLOAT xBase = static_cast<int>(floor(static_cast<float>(width - 1) / static_cast<float>(reWidth - 1) * 1000.0f)) / 1000.0f;
	C_FLOAT yBase = static_cast<int>(floor(static_cast<float>(height - 1) / static_cast<float>(reHeight - 1) * 1000.0f)) / 1000.0f;

	C_FLOAT xProportion = static_cast<float>(reWidth) / static_cast<float>(width);
	C_FLOAT yProportion = static_cast<float>(reHeight) / static_cast<float>(height);
	C_FLOAT xOffset = xProportion - floor(xProportion); // 左邊權重比例
	C_FLOAT yOffset = yProportion - floor(yProportion); // 上邊權重比例

	//(0, 0), (0, 1), (1, 0), (1, 1)
	C_FLOAT w1 = (1.0f - xOffset) * (1.0f - yOffset);
	C_FLOAT w2 = (1.0f - xOffset) * yOffset;
	C_FLOAT w3 = xOffset * (1.0f - yOffset);
	C_FLOAT w4 = xOffset * yOffset;

	for (UINT32 row = 0; row < reHeight; row++)
	{
		float y = row * yBase;
		C_UINT32 y1 = static_cast<UINT32>(floor(y));
		C_UINT32 y2 = static_cast<UINT32>(ceil(y));

		for (UINT32 col = 0; col < reWidth; col++)
		{
			float x = col * xBase;
			C_UINT32 x1 = static_cast<UINT32>(floor(x));
			C_UINT32 x2 = static_cast<UINT32>(ceil(x));
			float pix = static_cast<float>(srcImage.image[y1][x1]) * w1
				+ static_cast<float>(srcImage.image[y1][x2]) * w2
				+ static_cast<float>(srcImage.image[y2][x1]) * w3
				+ static_cast<float>(srcImage.image[y2][x2]) * w4;

			purImage.image[row][col] = static_cast<UINT32>(pix);
		}
	}
}

void Library::PyramidDown8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	UCHAE* data = new UCHAE[width * height];

	BlurGauss8bit(src, data
		, width, height
		, 5, 1.0f);

	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 srcRow = 0; srcRow < height; srcRow += 2)
	{
		for (UINT32 srcCol = 0; srcCol < width; srcCol += 2)
		{
			*pur = srcImage.image[srcRow][srcCol];
			pur++;
		}
	}

	delete[] data;
	data = nullptr;
}

void Library::PyramidUp8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	C_UINT32 purWidth = width << 1;
	C_UINT32 purHeight = height << 1;
	//UCHAE* data = new UCHAE[purWidth * purHeight];
	Image dataImage(pur, purWidth, purHeight, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 purRow = 0; purRow < purHeight; purRow += 2)
	{
		for (UINT32 purCol = 0; purCol < purWidth; purCol += 2)
		{
			dataImage.image[purRow][purCol] = *src;
			dataImage.image[purRow + 1][purCol] = *src;
			dataImage.image[purRow][purCol + 1] = *src;
			dataImage.image[purRow + 1][purCol + 1] = *src;
			src++;
		}
	}


	//BlurGauss8bit(data, pur
	//	, purWidth, purHeight
	//	, 5, 1.0f);

	//delete[] data;
	//data = nullptr;
}

void Library::SetAffineTransform(float** affine
	, float* baseX, float* baseY
	, C_UINT32 row, C_UINT32 col)
{
	GaussianElimination gauss(affine, row, col);

	gauss.Compute();

	for (UINT32 index = 0; index < row; index++)
	{
		baseX[index] = affine[index][col - 2];
		baseY[index] = affine[index][col - 1];
	}
}

void Library::Affine8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT* baseX, C_FLOAT* baseY)
{
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 row = 0; row < height; row++)
	{
		for (UINT32 col = 0; col < width; col++)
		{
			C_UINT32 newRow = static_cast<UINT32>(col * baseY[0] + row * baseY[1] + baseY[2]);
			C_UINT32 newCol = static_cast<UINT32>(col * baseX[0] + row * baseX[1] + baseX[2]);
			if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
			{
				purImage.image[newRow][newCol] = srcImage.image[row][col];
			}
		}
	}
}

void Library::SetSobelKernels(int32_t* kernels
	, const bool dx, const bool dy)
{
	if (!dx && dy)
	{
		//int32_t arrays[9] = { -3, -10, -3, 0, 0, 0, 3, 10, 3 };
		int32_t arrays[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
		memcpy(kernels, arrays, sizeof(int32_t) * 9);
	}
	else if (dx && !dy)
	{
		//int32_t arrays[9] = { -3, 0, 3, -10, 0, 10, -3, 0, 3 };
		int32_t arrays[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
		memcpy(kernels, arrays, sizeof(int32_t) * 9);
	}
	else if (dx && dy)
	{
		int32_t arrays[9] = { -2, -2, 0, -2, 0, 2, 0, 2, 2 };
		memcpy(kernels, arrays, sizeof(int32_t) * 9);
	}
	else
	{
		int32_t arrays[9] = { 0, -2, -2, 2, 0, -2, 2, 2, 0 };
		memcpy(kernels, arrays, sizeof(int32_t) * 9);
	}
}

void Library::Sobel8bit(C_UCHAE* src, int32_t* data
	, C_UINT32 width, C_UINT32 height
	, const bool dx, const bool dy)
{
	// 1. padding
	C_UINT32 padWidth = width + 2;
	C_UINT32 padHeight = height + 2;
	UCHAE* padSrc = new UCHAE[padWidth * padHeight];

	ImagePadding8bit(src, padSrc, width, height, 1);


	// 2. set kernel
	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::GRAY_8BIT);
	int32_t kernels[9];

	SetSobelKernels(kernels
		, dx, dy);


	// 3. calculate convolution
	for (UINT32 row = 1; row < padWidth - 1; row++)
	{
		for (UINT32 col = 1; col < padHeight - 1; col++)
		{
			int32_t sum = 0;
			UINT32 kernelsIndex = 0;

			for (int32_t blockRow = -1; blockRow <= 1; blockRow++)
			{
				for (int32_t blockCol = -1; blockCol <= 1; blockCol++)
				{
					UCHAE pix = srcImage.image[row + blockRow][col + blockCol];

					sum += (static_cast<int32_t>(pix) * kernels[kernelsIndex]);
					kernelsIndex++;
				}
			}

			*data = sum;
			data++;
		}
	}

	delete[] padSrc;
	padSrc = nullptr;
}

void Library::SobelEdgeView8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height)
{
	// 1. get sobel
	int32_t* Gx = new int32_t[width * height];
	int32_t* Gy = new int32_t[width * height];
	C_UCHAE* srcEnd = src + width * height;

	Sobel8bit(src, Gx
		, width, height
		, true, false);

	Sobel8bit(src, Gy
		, width, height
		, false, true);


	// 2. calculate abs and get max
	int32_t max = 0;
	int32_t* data = new int32_t[width * height];
	int32_t* dataPointer = data;
	int32_t* GxPointer = Gx;
	int32_t* GyPointer = Gy;

	while (src < srcEnd)
	{
		*dataPointer = abs(*GxPointer) + abs(*GyPointer);
		max = max < *dataPointer ? *dataPointer : max;

		dataPointer++;
		src++;
		GxPointer++;
		GyPointer++;
	}

	delete[] Gx;
	Gx = nullptr;

	delete[] Gy;
	Gy = nullptr;



	// 3. normalization
	C_UCHAE* purEnd = pur + width * height;
	dataPointer = data;

	while (pur < purEnd)
	{
		*pur = *dataPointer * 255 / max;

		dataPointer++;
		pur++;
	}

	delete[] data;
	data = nullptr;
}

void Library::Sobel24bit(C_UCHAE* src, int32_t* data
	, C_UINT32 width, C_UINT32 height
	, const bool dx, const bool dy)
{
	C_UINT32 padWidth = width + 2;
	C_UINT32 padHeight = height + 2;
	UCHAE* padSrc = new UCHAE[padWidth * padHeight * 3];

	ImagePadding24bit(src, padSrc, width, height, 1);


	// Sobel
	Image srcImage(padSrc, padWidth, padHeight, MNDT::ImageType::BGR_24BIT);
	int32_t kernels[9];

	SetSobelKernels(kernels
		, dx, dy);

	for (UINT32 row = 1; row < padWidth - 1; row++)
	{
		for (UINT32 col = 1; col < padHeight - 1; col++)
		{
			int32_t bSum = 0;
			int32_t gSum = 0;
			int32_t rSum = 0;
			UINT32 kernelsIndex = 0;

			for (int32_t blockRow = -1; blockRow <= 1; blockRow++)
			{
				for (int32_t blockCol = -1; blockCol <= 1; blockCol++)
				{
					Pixel pix = srcImage.GetPixel(row + blockRow, col + blockCol);

					bSum += (static_cast<int32_t>(pix.B) * kernels[kernelsIndex]);
					gSum += (static_cast<int32_t>(pix.G) * kernels[kernelsIndex]);
					rSum += (static_cast<int32_t>(pix.R) * kernels[kernelsIndex]);
					kernelsIndex++;
				}
			}

			*data = bSum;
			data++;
			*data = gSum;
			data++;
			*data = rSum;
			data++;
		}
	}

	delete[] padSrc;
	padSrc = nullptr;
}


void Library::SobelVisualization24bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, const bool dx, const bool dy)
{
	// Sobel
	int32_t max[3] = { 0, 0, 0 };
	int32_t* data = new int32_t[width * height * 3];

	Sobel24bit(src, data
		, width, height
		, dx, dy);


	// normalization
	int32_t* dataHead = data;

	for (UINT32 row = 0; row < width; row++)
	{
		for (UINT32 col = 0; col < height; col++)
		{
			C_INT32 B = abs(*dataHead);
			dataHead++;

			C_INT32 G = abs(*dataHead);
			dataHead++;

			C_INT32 R = abs(*dataHead);
			dataHead++;

			if (max[0] < B) max[0] = B;
			if (max[1] < G) max[1] = G;
			if (max[2] < R) max[2] = R;
		}
	}

	Image purImage(pur, width, height, MNDT::ImageType::BGR_24BIT);

	dataHead = data;

	for (UINT32 row = 0; row < width; row++)
	{
		for (UINT32 col = 0; col < height; col++)
		{
			C_UCHAE B = static_cast<UCHAE>(*dataHead * 255 / max[0]);
			dataHead++;

			C_UCHAE G = static_cast<UCHAE>(*dataHead * 255 / max[1]);
			dataHead++;

			C_UCHAE R = static_cast<UCHAE>(*dataHead * 255 / max[2]);
			dataHead++;

			Pixel pix(static_cast<UCHAE>(B), static_cast<UCHAE>(G), static_cast<UCHAE>(R));

			purImage.SetPixel(row, col, pix);
		}
	}

	delete[] data;
	data = nullptr;
}

void Library::CartToPolar(C_INT32* Gx, C_INT32* Gy
	, C_UINT32 width, C_UINT32 height
	, float* magnitude, float* angles
	, MNDT::ImageType type)
{
	const double angle = 180.0 / MNDT::PI;
	C_UINT32 size = width * height * type;
	C_INT32* GxEnd = Gx + size;

	while (Gx < GxEnd)
	{
		*magnitude = static_cast<float>(sqrt((*Gx) * (*Gx) + (*Gy) * (*Gy)));
		*angles = static_cast<float>(abs(atan2(*Gy, *Gx) * angle));

		Gx++;
		Gy++;
		angles++;
		magnitude++;
	}
}

void Library::Gamma8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_DOUBLE gamma)
{
	UCHAE gammaLUT[256];

	for (UINT32 index = 0; index < 256; index++)
	{
		double pix = (index + 0.5) / 256.0; //歸一化
		pix = pow(pix, gamma);
		gammaLUT[index] = static_cast<UCHAE>((pix * 256 - 0.5)); //反歸一化
	}

	UCHAE* purEnd = pur + width * height;

	while (pur < purEnd)
	{
		*pur = gammaLUT[*src];
		pur++;
		src++;
	}
}

//void Library::HoughLines(C_UCHAE* src, UCHAE* pur
//	, C_UINT32 width, C_UINT32 height
//	, C_FLOAT rho, C_FLOAT theta, C_FLOAT threshold)
//{
//	C_FLOAT fixRho = 1.0f / rho;
//	C_UINT32 thetaSize = static_cast<UINT32>(MNDT::PI / theta);
//	float* fixSin = new float[thetaSize];
//	float* fixCos = new float[thetaSize];
//
//	for (UINT32 index = 0; index < thetaSize; index++)
//	{
//		fixSin[index] = MNDT::FixValue(sin(theta * index)) * fixRho;
//		fixCos[index] = MNDT::FixValue(cos(theta * index)) * fixRho;
//	}
//
//	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
//	C_DOUBLE originalR = std::max((width + height) * sin(MNDT::PI / 4.0), static_cast<double>(std::max(width, height)));
//	//C_DOUBLE originalR = 14 * sin(MNDT::PI / 4.0);
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
//	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);
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
//			MNDT::DrawLine8bit(purImage, Point(x1, y1), Point(x2, y2));
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
//			MNDT::DrawLine8bit(purImage, Point(x1, y1), Point(x2, y2));
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

void Library::HoughLines(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT rho, C_FLOAT theta, C_UINT32 threshold)
{
	// 1. init params
	C_FLOAT fixRho = 1.0f / rho;
	C_UINT32 thetaSize = static_cast<UINT32>(MNDT::PI / theta);
	float* fixSin = new float[thetaSize];
	float* fixCos = new float[thetaSize];

	for (UINT32 index = 0; index < thetaSize; index++)
	{
		fixSin[index] = MNDT::FixValue(sin(theta * index)) * fixRho;
		fixCos[index] = MNDT::FixValue(cos(theta * index)) * fixRho;
	}

	// 2. hough total
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	C_DOUBLE originalR = std::max((width + height) * sin(MNDT::PI / 4.0), static_cast<double>(std::max(width, height)));
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
	//DrawHoughPolar(pur
	//	, width, height
	//	, count
	//	, theta, maxR);

	// 3. update neighbours
	HoughLineNeighboursUpdate(count
		, thetaSize, maxR
		, threshold);


	// 4. draw line
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

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

void Library::DrawHoughPolar(UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32* count
	, C_FLOAT theta, C_UINT32 maxR)
{
	C_UINT32 thetaSize = static_cast<UINT32>(MNDT::PI / theta);
	C_UINT32 xAxisOffset = maxR * (thetaSize + 2);
	C_UINT32 halfHeight = height >> 1;
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

	for (UINT32 index = 0; index < thetaSize; index++)
	{
		C_UINT32 x = static_cast<UINT32>(theta * index / MNDT::PI * width);
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

					MNDT::DrawPoint8bit(purImage, point);
				}
			}
		}
	}
}

void Library::HoughLineNeighboursUpdate(UINT32* count
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


void Library::HoughCircles(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_FLOAT minRadius, C_FLOAT maxRadius, C_UINT32 threshold)
{
	// 1. total
	UINT32* count = new UINT32[(width + 2) * (height + 2)]{ 0 };

	HoughCirclesCount(src
		, width, height
		, count
		, minRadius, maxRadius);


	// 2. update neighbours
	HoughCircleNeighboursUpdate(count
		, width, height
		, threshold);

	// 3. draw
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);
	Image purImage(pur, width, height, MNDT::ImageType::GRAY_8BIT);

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

				for (float pi = 0; pi <= MNDT::PI * 2; pi += 0.2f)
				{
					int32_t y = static_cast<int32_t>(static_cast<float>(row) + MNDT::FixValue(sin(pi)) * radius);
					int32_t x = static_cast<int32_t>(static_cast<float>(col) + MNDT::FixValue(cos(pi)) * radius);

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

				for (float pi = 0; pi <= MNDT::PI * 2; pi += 0.2f)
				{
					C_UINT32 y = static_cast<UINT32>(row + MNDT::FixValue(sin(pi)) * radius);
					C_UINT32 x = static_cast<UINT32>(col + MNDT::FixValue(cos(pi)) * radius);

					purImage.image[y][x] = 255;
				}
			}
		}
	}

	delete[] count;
	count = nullptr;
}

void Library::HoughCirclesCount(C_UCHAE* src
	, C_UINT32 width, C_UINT32 height
	, UINT32* count
	, C_FLOAT minRadius, C_FLOAT maxRadius)
{
	assert(count != nullptr);

	// get gradient
	Library lib;
	int32_t* Gx = new int32_t[width * height];
	int32_t* Gy = new int32_t[width * height];

	lib.Sobel8bit(src, Gx
		, width, height
		, true, false);

	lib.Sobel8bit(src, Gy
		, width, height
		, false, true);

	// calculate gradient total
	Image srcImage(const_cast<UCHAE*>(src), width, height, MNDT::ImageType::GRAY_8BIT);

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
						//MNDT::DrawLine8bit(purImage, Point(col, row), Point(static_cast<UINT32>(x), static_cast<UINT32>(y)));
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

void Library::HoughCirclePointCount(UINT32* count
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


void Library::HoughCircleNeighboursUpdate(UINT32* count
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 threshold)
{
	// 4鄰比較
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

void Library::Threshold8bit(C_UCHAE* src, UCHAE* pur
	, C_UINT32 width, C_UINT32 height
	, C_UINT32 thresh)
{
	assert(src != nullptr && pur != nullptr);
	assert(width > 0 && height > 0);

	C_UCHAE* purEnd = pur + width * height;

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