/*
 * $File: structure.h
 * $Date: Fri Dec 03 11:06:12 2010 +0800
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
#include "xb_cube.h"

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

#define CUBE_STATE_FIX						0x00
#define CUBE_STATE_ROT_RIGHT_0				0x01
#define CUBE_STATE_ROT_RIGHT_1				0x02
#define CUBE_STATE_ROT_LEFT_0				0x03
#define CUBE_STATE_ROT_LEFT_1				0x04
#define CUBE_STATE_ROT_UP_0					0x05
#define CUBE_STATE_ROT_UP_1					0x06
#define CUBE_STATE_ROT_DOWN_0				0x07
#define CUBE_STATE_ROT_DOWN_1				0x08
#define CUBE_STATE_ROT_FRONT_0				0x09
#define CUBE_STATE_ROT_FRONT_1				0x0A
#define CUBE_STATE_ROT_BACK_0				0x0B
#define CUBE_STATE_ROT_BACK_1				0x0C

class Cube
{
	public:
		class CubeGrid
		{
			public:
				int id;
				Point center;
				// front back top bottom right left
				Colorf color[6];
				bool visibility[6];
				void set_default(int id, const Point &center);
				void draw(GLfloat len, GLfloat padding, const Colorf &padding_color) const;
		};
		int size;
		GLfloat grid_len;
		CubeGrid *grid;
		Colorf padding_color;
		GLfloat padding;
		/*
		 * The cube is set to a reserved cube by default
		 */
		Cube(int size = 3, GLfloat grid_len = 1.0f, GLfloat padding = 0.04, const Colorf &pading_color = Colorf(0, 0, 0));
		void reset();
		void set_default(int size = 3, GLfloat grid_len = 1.0f, GLfloat padding = 0.04, const Colorf &pading_color = Colorf(0, 0, 0));
		void draw(const Point &center) const;
		int state;
};
#endif // __CUBE_STRUCTURE_H__

