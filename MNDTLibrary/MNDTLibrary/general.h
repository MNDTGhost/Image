#pragma once
#ifndef GENERAL_H
#define GENERAL_H
//#define NDEBUG
#include <fstream>
#include <string>
#include <algorithm>
#include <assert.h>

typedef unsigned char UCHAE;
typedef const unsigned char C_UCHAE;
typedef const char C_CHAE;
typedef unsigned __int32 UINT32;
typedef const unsigned __int32 C_UINT32;
typedef const __int32 C_INT32;
typedef const double C_DOUBLE;
typedef const float C_FLOAT;


namespace MNDT {
	enum ImageType
	{
		BGR_32BIT = 3,
		GRAY_8BIT = 1
	};

	template <typename T>
	inline void Write(T& data)
	{
		std::fstream fwLog;

		fwLog.open(MNDT::LOG_FILE, std::ios::app);
		fwLog << data;
		fwLog.close();
	}

	extern char* LOG_FILE;
	extern double PI;
}
#endif // !GENERAL_H
