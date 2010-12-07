/*
 * $File: cube.h
 * $Date: Tue Dec 07 10:16:47 2010 +0800
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

#ifndef HEADER_CUBE
#define HEADER_CUBE

#include <list>
#include "header.h"
#include "math.h"
#include "color.h"

class Cubie;

class Cube
{
	public:
		Cube(int xlen = 3, int ylen = 3, int zlen = 3);
		~Cube();
		
		void moveSlice(Axis axis, int location, Rotation direction);
	private:
		Point size;
		std::list<Cubie *> cubies;
		void deleteCubies();
};

class Sticker
{
	public:
		Sticker();
		~Sticker();
		Colorf color;
		Point current_center;
		Point original_center;
};

class Cubie
{
	public:
		Cubie(const Point &center);
		~Cubie();
		void rotate(Axis axis, int location, Rotation direction);
	private:
		Point original_center;
		Point current_center;
		std::list<Sticker *> stickers;
};

#endif // HEADER_CUBE
