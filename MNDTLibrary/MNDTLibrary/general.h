#pragma once
#ifndef GENERAL_H
#define GENERAL_H
#include <fstream>
#include <string>
#include <algorithm>

#ifdef DEBUG
#include <assert.h>
#endif // DEBUG


typedef unsigned char UCHAE;
typedef const unsigned char C_UCHAE;
typedef const char C_CHAE;
typedef unsigned __int32 UINT32;
typedef const unsigned __int32 C_UINT32;
typedef const __int32 C_INT32;
typedef const double C_DOUBLE;


namespace MNDT {

	// 刪除單指標，使用雙重指標指向傳入的指標，直接對原先地址刪除
	template <class T>
	inline void DeletePtr(T** ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}

	extern void Write(C_UCHAE* str);

	extern char* LOG_FILE;
}
#endif // !GENERAL_H
