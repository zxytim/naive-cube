/*
 * $File: structure.cpp
 * $Date: Wed Dec 01 10:56:43 2010 +0800
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
#include "structure.h"

bool Cube::is_completed()
{
}

void Cube::rotate(int x, int y, int z, int axis)
{
}

Quad::Quad(const Point &normalv, const Point &v0, const Point &v1, const Point &v2, const Point &v3)
{
	normal = normalv;
	vtx[0] = v0;
	vtx[1] = v1;
	vtx[2] = v2;
	vtx[3] = v3;
}
