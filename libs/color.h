/*
 * $File: color.h
 * $Date: Thu Dec 02 18:09:23 2010 +0800
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
/* color definations */
#ifndef __CUBE_COLOR_H__
#define __CUBE_COLOR_H__

#include <GL/gl.h>

class Colorf
{
	public:
		GLfloat r, g, b, a;
		Colorf();
		Colorf(GLfloat r = 0, GLfloat g = 0, GLfloat b = 0, GLfloat a = 1);
};

#endif
