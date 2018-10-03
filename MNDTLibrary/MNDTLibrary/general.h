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

	// �R������СA�ϥ��������Ы��V�ǤJ�����СA���������a�}�R��
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
