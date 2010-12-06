/*
 * $File: cube.cpp
 * $Date: Mon Dec 06 18:53:15 2010 +0800
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
}

void Cube::deleteCubies()
{
	for (std::list<Cubie *>::iterator cubie = cubies.begin(); 
			cubie != cubies.end(); cubie ++)
		delete (*cubie);
}

Sticker::Sticker()
{
}

Sticker::~Sticker()
{
}

Cubie::Cubie()
{
}

Cubie::~Cubie()
{
	for (std::list<Sticker *>::iterator sticker = stickers.begin(); 
			sticker != stickers.end(); sticker ++)
		delete (*sticker);
}


