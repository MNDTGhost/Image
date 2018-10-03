#include "general.h"

extern void MNDT::Write(C_UCHAE* str)
{
	std::fstream fwLog;

	fwLog.open(MNDT::LOG_FILE, std::ios::app);
	fwLog << str;
	fwLog.close();
}


extern char* MNDT::LOG_FILE = "D:\\Log.txt";