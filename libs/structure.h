/*
 * $File: structure.h
 * $Date: Wed Dec 01 10:56:46 2010 +0800
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
#ifndef __CUBE_STRUCTURE_H__
#define __CUBE_STRUCTURE_H__

#include "math.h"
#include "color.h"

class CubeGrid
{
	public:
		Color color[6];
};

class Cube
{
	public:
		CubeGrid grid[3][3][3];
		bool is_completed();
		void rotate(int x, int y, int z, int axis);
};

class Quad
{
	public:
		Point normal;
		Point vtx[4];
		Quad();
		Quad(const Point &normal, const Point &v0, const Point &v1, const Point &v2, const Point &v3);
		// TODO
		//bool bind_texture;
};
#endif
