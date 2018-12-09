#pragma once
#ifndef GENERAL_H
#define GENERAL_H
#include <vector>
#include <algorithm>

//#define NDEBUG
#include <assert.h>

typedef unsigned char UCHAR;
typedef const unsigned char C_UCHAR;
typedef const char C_CHAR;
typedef unsigned __int32 UINT32;
typedef const unsigned __int32 C_UINT32;
typedef const __int32 C_INT32;
typedef const double C_DOUBLE;
typedef const float C_FLOAT;
typedef const bool C_BOOL;

namespace AdaBoostType {
	typedef std::vector<double> DATA;
	typedef const std::vector<double> C_DATA;
	typedef std::vector<std::vector<double>> DATAS;
	typedef const std::vector<std::vector<double>> C_DATAS;
	typedef __int32 LABEL;
	typedef const __int32 C_LABEL;
	typedef std::vector<__int32> LABELS;
	typedef const std::vector<__int32> C_LABELS;

}

#endif // GENERAL_H
