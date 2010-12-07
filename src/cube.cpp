/*
 * $File: cube.cpp
 * $Date: Tue Dec 07 10:41:28 2010 +0800
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

#include "cube.h"
#define foreach_sticker \
	for (std::list<Sticker *>::iterator sticker = stickers.begin(); \
			sticker != stickers.end(); sticker ++)
#define foreach_cubie \
	for (std::list<Cubie *>::iterator cubie = cubies.begin(); \
			cubie != cubies.end(); cubie ++)

Cube::Cube(int xlen, int ylen, int zlen)
{
	size[0] = xlen;
	size.y = ylen;
	size.z = zlen;
}

Cube::~Cube()
{
	deleteCubies();
}

void Cube::moveSlice(Axis axis, int location, Rotation direction)
{
	if (size[axis + 1] != size[axis + 2])
		direction = ONE_EIGHTY;

	foreach_cubie
		(*cubie)->rotate(axis, location, direction);
}

void Cube::deleteCubies()
{
	foreach_cubie
		delete (*cubie);
}

Sticker::Sticker()
{
}

Sticker::~Sticker()
{
}

Cubie::Cubie(const Point &center)
{
	original_center = current_center = center;
}

Cubie::~Cubie()
{
	foreach_sticker
		delete (*sticker);
}

void Cubie::rotate(Axis axis, int location, Rotation direction)
{
	if (current_center[axis] != location)
		return;

	Coord_t t;
	switch (direction)
	{
		case ANTICLOCKWISE:
#define ROTATE_ANTICLOCKWISE(p) \
			{t = p[axis + 1]; p[axis + 1] = - p[axis + 2]; p[axis + 2] = t;}
			ROTATE_ANTICLOCKWISE(current_center);
			foreach_sticker
				ROTATE_ANTICLOCKWISE((*sticker)->current_center);
#undef ROTATE_ANTICLOCKWISE
			break;
		case CLOCKWISE:
#define ROTATE_CLOCKWISE(p) \
			{t = p[axis + 1]; p[axis + 1] = p[axis + 2]; p[axis + 2] = -t;}
			ROTATE_CLOCKWISE(current_center);
			foreach_sticker
				ROTATE_CLOCKWISE((*sticker)->current_center);
#undef ROTATE_CLOCKWISE
			break;
		case ONE_EIGHTY:
#define ROTATE_ONE_EIGHTY(p) \
			{p[axis + 1] = - p[axis + 1]; p[axis + 2] = - p[axis + 2];}
			ROTATE_ONE_EIGHTY(current_center);
			foreach_sticker
				ROTATE_ONE_EIGHTY((*sticker)->current_center);
#undef ROTATE_ONE_EIGHTY
			break;
	}

}

