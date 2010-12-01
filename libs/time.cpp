/*
 * $File: time.cpp
 * $Date: Wed Dec 01 10:56:49 2010 +0800
 * $Author: Zhou Xinyu <zxytim@gmail.com>
 */
/*
   This file is part of naive-cube

   Copyright (C) <2010>  Zhou Xinyu <zxytim@gmail.com>

   naive-cube is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   naive-cube is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with JKOS.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifdef unix
#include <sys/time.h>
#else // windows
#include <windows.h>
#endif

#include "time.h"

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

