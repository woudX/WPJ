#ifndef _H_WPJTIME
#define _H_WPJTIME
#define _CRT_SECURE_NO_WARNINGS

#include "WPJMacros.h"
#include "WPJStdafx.h"

#include <Windows.h>
#include <ctime>

NS_WPJ_BEGIN

class TimeVal 
{
public:
	long tv_sec;	// second
	long tv_msec;	// micro second
};

class WPJTime
{
public:
	static int GetTimeOfDay(TimeVal *p_pTimeVal);
	static time_t obTime;
	static char* NowTime();
	
};

NS_WPJ_END


#endif