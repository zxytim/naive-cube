/*
 * $File: math.h
 * $Date: Tue Dec 07 10:30:27 2010 +0800
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

#ifndef HEADER_MATH
#define HEADER_MATH

#include "header.h"

#include <GL/gl.h>


class Point;

typedef Point Vector;

typedef float Coord_t;
#define EPS 1e-7

class Point
{
	public:
		Coord_t x, y, z;

		Point();
		Point(Coord_t x, Coord_t y, Coord_t z);
		~Point();

		void set(Coord_t x, Coord_t y, Coord_t z);
		void setLength(Coord_t len);

		Point operator + (const Point &p) const;
		Point operator - (const Point &p) const;
		Coord_t operator * (const Point &p) const; // This is dot product
		Point operator ^ (const Point &p) const; // This is cross product

		Point operator * (const Coord_t factor) const;
		Point operator / (const Coord_t factor) const;

		Point operator += (const Point &p);
		Point operator -= (const Point &p);
		Point operator *= (const Coord_t factor);
		Point operator /= (const Coord_t factor);

		Coord_t mo() const;
		Coord_t invMo() const;
		Point unit() const;
		Point resize(Coord_t len) const;
		Point rotate(const Vector &axis, Coord_t angle) const;

		bool is_zero() const;
		Coord_t getAngle(const Point &v) const;

		Coord_t& operator [] (int index);

};

float invSqrt(float x);

#endif // HEADER_MATH
