/*
 * $File: timer.cpp
 * $Date: Mon Dec 06 16:03:27 2010 +0800
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
   along with naive-cube.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifdef unix
#include <sys/time.h>
#include <unistd.h>
#elif defined(__WIN32__)
#include <windows.h>
#endif

#include "timer.h"

static Time_t time_prec_div[] = {1000000, 1000, 1};
static Time_t time_us();
static Time_t toMs(Time_t time, TimerPrecision prec);

Timer::Timer()
{
	precision = TIMER_PRECISION_MS;
}

Timer::~Timer()
{
}

Time_t Timer::time()
{
	return time_us() / time_prec_div[precision];
}

Time_t Timer::begin()
{
	time_begin = time_us();
	return time_begin / time_prec_div[precision];
}

Time_t Timer::end()
{
	return (time_us() - time_begin) / time_prec_div[precision];
}

void Timer::sleep(Time_t time)
{
	time = toMs(time, precision);
#ifdef unix
	usleep(time);
#elif defined(__WIN32__)
	Sleep(time);
#endif
}

void Timer::setPrecision(TimerPrecision tp)
{
}


#ifdef __WIN32__
Time_t getFreq()
{
	static bool freq_getted = false;
	static Time_t freq;
	if (!freq_getted)
	{
		LARGE_INTEGER nFreq;
		if (!QueryPerformanceFrequency(&nFreq))
		{
			freq = nFreq.QuadPart;
			freq_getted = true;
		}
		else
		{
			// TODO
		}
	}
	return freq;
}

#endif

Time_t time_us()
{
#ifdef unix
	timeval tv;
	gettimeofday(&tv, 0);
	return (Time_t)tv.tv_sec * (Time_t)1000000 + (Time_t)tv.tv_usec;
#elif defined(__WIN32__)
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return ((Time_t)t.QuadPart * (Time_t)1000000/ getFreq());
#else
	return -1;
#endif
}


Time_t toMs(Time_t time, TimerPrecision prec)
{
	if (prec == TIMER_PRECISION_S)
		return time * 1000;
	if (prec == TIMER_PRECISION_MS)
		return time;
	if (prec = TIMER_PRECISION_US)
		return time / 1000;
}

