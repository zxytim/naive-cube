
#ifdef unix
#include <sys/time.h>
#else // windows
#include <windows.h>
#endif

#include "cube_time.h"

#define TIME_UNIT_MAX (TIME_UNIT_US + 1)

const Time_t time_unit_div[] = {1000000, 1000, 1};

#ifndef unix
Time_t getFreq()
{
	static bool freq_getted = false;
	static Time_t freq;
	if (!freq_getted)
	{
		LARGE_INTEGER nFreq;
		QueryPerformanceFrequency(&nFreq);
		freq = nFreq.QuadPart;
		freq_getted = true;
	}
	return freq;
}
#endif

// return -1 if error
Time_t timeGetTime(int unit)
{
	if (unit < 0 || unit >= TIME_UNIT_MAX)
		return -1;
#ifdef unix
	static timeval tv;
	gettimeofday(&tv, 0);
	Time_t t = tv.tv_sec * 1000000ll + tv.tv_usec;
	return t / time_unit_div[unit];
#else // XXX no tested yet
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (t.QuadPart / getFreq()) / time_unit_div[unit];
#endif
}

static Time_t time_start = 0;
void timeStart()
{
	time_start = timeGetTime(TIME_UNIT_US);
}

Time_t timeEnd(int unit)
{
	if (unit < 0 || unit >= TIME_UNIT_MAX)
		return -1;
	return (timeGetTime(TIME_UNIT_US) - time_start) / time_unit_div[unit];
}

