#include "WPJDebug.h"

USING_NS_WPJ

time_t WPJTime::obTime;

char* WPJTime::NowTime()
{
	time(&obTime);
	char* t_obTime(ctime(&obTime));

	t_obTime[strlen(t_obTime) - 1] = '\0';

	return t_obTime;
}