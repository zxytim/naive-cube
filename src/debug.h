/*
 * $File: debug.h
 * $Date: Mon Dec 06 21:53:03 2010 +0800
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

#ifndef HEADER_DEBUG
#define HEADER_DEBUG

#define DEBUG_LEVEL_DEBUG		0
#define DEBUG_LEVEL_INFO		1
#define DEBUG_LEVEL_WARNING		2
#define DEBUG_LEVEL_ERROR		3
#define DEBUG_LEVEL_CRITICAL	4

class Debug
{
	public:
		Debug();
		Debug(std::string log_file);
		void debug();
};

#endif // HEADER_DEBUG
