#include "WPJTime.h"

USING_NS_WPJ

int WPJTime::GetTimeOfDay(TimeVal *p_pTimeVal) 
{
	LARGE_INTEGER t_obLIFreq;
	LARGE_INTEGER t_obLICount;

	QueryPerformanceFrequency(&t_obLIFreq);
	QueryPerformanceCounter(&t_obLICount);

	p_pTimeVal->tv_sec = static_cast<long>(t_obLICount.QuadPart / t_obLIFreq.QuadPart);
	p_pTimeVal->tv_msec = static_cast<long>(t_obLICount.QuadPart * 1000000 / t_obLIFreq.QuadPart - p_pTimeVal->tv_sec * 1000000);

	return 0;
}

time_t WPJTime::obTime;

char* WPJTime::NowTime()
{
	time(&obTime);
	char* t_obTime(ctime(&obTime));

	t_obTime[strlen(t_obTime) - 1] = '\0';

	return t_obTime;
}