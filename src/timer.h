/*
 * $File: timer.h
 * $Date: Mon Dec 06 16:03:32 2010 +0800
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

#ifndef HEADER_TIMER
#define HEADER_TIMER

typedef long long Time_t;

enum TimerPrecision
{
	TIMER_PRECISION_S,		// second
	TIMER_PRECISION_MS,		// millisecond
	TIMER_PRECISION_US		// microsecond
};

/*
 * Default timer precision is millisecond
 */
class Timer
{
	public:
		Timer();
		~Timer();
		Time_t time();
		Time_t begin();
		Time_t end();
		void sleep(Time_t time);
		void setPrecision(TimerPrecision tp);

	private:
		TimerPrecision precision;
		Time_t time_begin;
};

#endif // HEADER_TIMER
