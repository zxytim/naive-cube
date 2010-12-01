/*
 * $File: math.h
 * $Date: Wed Dec 01 10:56:39 2010 +0800
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
#ifndef __LIBS_CUBE_MATH_H__
#define __LIBS_CUBE_MATH_H__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>

#define PI 3.141592653589793236
#define EPS 1e-7

class Point
{
	public:
		GLfloat x, y, z;
		Point();
		Point(GLfloat x, GLfloat y, GLfloat z);
		void set(GLfloat x, GLfloat y, GLfloat z);
		friend Point operator + (const Point &a, const Point &b);
		friend Point operator - (const Point &a, const Point &b);
		friend GLfloat operator * (const Point &a, const Point &b);
		friend Point operator * (const Point &a, GLfloat factor);
		friend Point operator / (const Point &a, GLfloat factor);
		friend bool operator == (const Point &a, const Point &b);
		friend bool operator != (const Point &a, const Point &b);
		Point& operator += (const Point &a);
		Point& operator -= (const Point &a);
		Point& operator *= (GLfloat factor);
		Point& operator /= (GLfloat factor);
		friend Point CrossProduct(const Point &a, const Point &b);
		GLfloat mo() const;
		Point unit() const;
		bool is_zero() const;
		Point resize(GLfloat len) const;
		Point rotate(Point axis, GLfloat angle);
		friend void vector_rotate(Point &vec, const Point &axis, GLfloat angle);
		GLfloat get_angle(const Point &v) const;
		friend GLfloat get_angle(const Point &a, const Point &b);
};

typedef Point Vector;

#endif // __LIBS_CUBE_MATH_H__
