/*
 * $File: common.cpp
 * $Date: Mon Dec 06 21:20:48 2010 +0800
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

#include "common.h"
#include <cstdarg>
#include <cstdlib>
#include <cstdio>

std::string __(std::string fmt, ...)
{
	int n, size = 100;
	va_list ap;
	char *p, *np;
	std::string ret;

	if ((p = (char *)malloc(size)) == NULL)
		return NULL;

	while (1)
	{
		va_start(ap, fmt);
		n = vsnprintf(p, size, fmt.data(), ap);
		va_end(ap);

		if (n > -1 && n < size)
		{
			ret = p;
			break;
		}
		if (n > -1)
			size = n + 1;
		else
			size <<= 1;
		if ((np = (char *)realloc(p, size)) == NULL)
		{
			free(p);
			return NULL;
		}
		else
			p = np;
	}
	return ret;
}

void print_str(FILE *file, std::string msg)
{
	fprintf(file, "%s\n", msg.c_str());
}

std::string itos(int num)
{
	static char s[11];
	std::string ret;
	if (num == 0) return "0";
	if (num < 0) ret = "-", num = -num;
	int cnt = 0;
	while (num)
		s[cnt ++] = num % 10, num /= 10;
	while (cnt --)
		ret += s[cnt];
	return ret;
}

