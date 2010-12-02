/*
 * $File: structure.h
 * $Date: Thu Dec 02 20:43:19 2010 +0800
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
#ifndef __CUBE_STRUCTURE_H__
#define __CUBE_STRUCTURE_H__

#include "math.h"
#include "color.h"
#include <GL/gl.h>

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

class CubeGrid
{
	public:
		// front back top bottom right left
		Colorf color[6];
		bool visible[6];
};

class Cube
{
	public:
		GLfloat cube_grid_len;
		CubeGrid grid[3][3][3];
};
#endif
