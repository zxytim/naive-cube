/*
 * $File: math.cpp
 * $Date: Tue Dec 07 10:30:25 2010 +0800
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

#include <cmath>

#include "math.h"

Point::Point()
{
}

Point::Point(Coord_t x_, Coord_t y_, Coord_t z_)
{
	x = x_, y = y_, z = z_;
}

Point::~Point()
{
}

void Point::set(Coord_t x_, Coord_t y_, Coord_t z_)
{
	x = x_, y = y_, z = z_;
}

void Point::setLength(Coord_t len)
{
	(*this) = (*this) * invMo() * len;
}


Point Point::operator + (const Point &p) const
{
	return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator - (const Point &p) const
{
	return Point(x - p.x, y - p.y, z - p.z);
}

Coord_t Point::operator * (const Point &p) const
{
	return x * p.x + y * p.y + z * p.z;
}

Point Point::operator ^ (const Point &p) const
{
	return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
}

Point Point::operator * (const Coord_t factor) const
{
	return Point(x * factor, y * factor, z * factor);
}

Point Point::operator / (const Coord_t factor) const
{
	return Point(x / factor, y / factor, z / factor);
}

Point Point::operator += (const Point &p)
{
	x += p.x;
	y += p.y;
	z += p.z;
	return *this;
}

Point Point::operator -= (const Point &p)
{
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return *this;
}

Point Point::operator *= (const Coord_t factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

Point Point::operator /= (const Coord_t factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	return *this;
}


Coord_t Point::mo() const
{
	return sqrt(x * x + y * y + z * z);
}

/*
 * The code below is from internet, which is adapted from part of 
 * the source codes of Quake3 Engine, written by John D. Carmack II.
 */
float invSqrt(float x)
{
	float xhalf = 0.5f * x;
	int i = * (int*) &x; // get bits for floating VALUE 
	i = 0x5f375a86 - (i >> 1); // gives initial guess y0
	x = *(float*)&i; // convert bits BACK to float
	x = x * (1.5f - xhalf * x * x); // Newton step, repeating increases accuracy
	return x;
}  

Coord_t Point::invMo() const
{
	return invSqrt(x * x + y * y + z * z);
}

Point Point::unit() const
{
	return (*this) * invMo();
}

Point Point::resize(Coord_t len) const
{
	return (*this) * invMo() * len;
}

Point Point::rotate(const Vector &axis, Coord_t angle) const
{
	Point vec = axis.unit();
	Point c = vec * ((*this) * vec);
	Point vert = (*this) - c;
	if (vert.is_zero())
		return *this;
	Coord_t inv_len = vert.invMo();
	vert = vert.unit();
	Point t = vert ^ vec;
	angle = angle * 0.0174532925199; // / 180.0 * M_PI;
	return (vert * cos(angle) + t * sin(angle)) * inv_len + c;
}

bool Point::is_zero() const
{
	return fabs(x) < EPS && fabs(y) < EPS && fabs(z) < EPS;
}

Coord_t Point::getAngle(const Point &v) const
{
	return acos((*this) * v * (invMo() * v.invMo() * 57.2957795131)); // / PI * 180;
}

Coord_t& Point::operator [] (int index)
{
	index %= 3;
	if (index < 0)
		index += 3;
	if (index == 0)
		return x;
	if (index == 1)
		return y;
	if (index == 2)
		return z;
}

