/*
 * $File: exception.cpp
 * $Date: Mon Dec 06 21:23:27 2010 +0800
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

#include "exception.h"
#include "common.h"

#include <cstdio>


static std::string MSG(std::string file, std::string func, int line, std::string error_msg)
{
	return (std::string)" throwed in " + file + ", function "
	   	+ func + ", line " + itos(line) + ": " + error_msg;
}

Exception::Exception(std::string file, std::string func, int line, std::string error_msg)
{
	exc_msg = "Exception" + MSG(file, func, line, error_msg);
}

Exception::~Exception()
{
}

std::string Exception::msg()
{
	return exc_msg;
}

void Exception::print()
{
	printf("%s\n", exc_msg.c_str());
}

