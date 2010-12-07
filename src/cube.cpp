/*
 * $File: cube.cpp
 * $Date: Tue Dec 07 16:18:36 2010 +0800
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
	deleteCubies();

	Point center;
	for (int i = 0; i < xlen; i ++)
	{
		center.x = 2 * i - xlen + 1;
		for (int j = 0; j < ylen; j ++)
		{
			center.y = 2 * j - ylen + 1;
			for (int k = 0; k < zlen; k ++)
			{
				center.z = 2 * k - zlen + 1;
				cubies.push_back(new Cubie(center));
			}
		}
	}
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

void Cube::addStickers()
{
	static Colorf color[] = 
	{
		Colorf(1, 0, 0), Colorf(0, 1, 0), Colorf(0, 0, 1),
		Colorf(1, 1, 0), Colorf(1, 0, 1), Colorf(0, 1, 1)
	};
	int cnt = 0;
	for (int i = 0; i < N_AXES; i ++)
		for (int j = 0; j < 2; j ++)
		{
			int sign = j * 2 - 1; // -1 or +1
			int location = sign * size[i];
			cnt ++;
			foreach_cubie
				(*cubie)->addSticker(color[cnt], (Axis)i, location);
		}
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

void Cubie::addSticker(const Colorf &color, Axis axis, int location)
{
	/*
	 * The cubie get a sticke on the face only if it is one the required face
	 */
	if (location - (location > 0 ? 1 : -1) != original_center[axis])
		return;
	
	Sticker *sticker = new Sticker();
	sticker->color = color;
	sticker->original_center = sticker->current_center = original_center;
	sticker->original_center[axis] = location;
	sticker->current_center[axis] = location;
	
	stickers.push_back(sticker);
}

