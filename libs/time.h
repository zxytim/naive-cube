/*
 * $File: time.h
 * $Date: Wed Dec 01 10:56:53 2010 +0800
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
#ifndef __LIBS_CUBE_TIME__
#define __LIBS_CUBE_TIME__

typedef long long Time_t;

#define TIME_UNIT_S				0x00
#define TIME_UNIT_MS			0x01
#define TIME_UNIT_US			0x02

// 
Time_t timeGetTime(int unit = TIME_UNIT_US);
void timeStart();
Time_t timeEnd(int unit = TIME_UNIT_US);

#endif // __LIBS_CUBE_TIME__

