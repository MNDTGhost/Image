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
	//assert(src != nullptr && pur != nullptr);
	//assert(width > 0 && height > 0);
	//Image imgSrc(src, width, height);
	//Image imgPur(pur, width, height);

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