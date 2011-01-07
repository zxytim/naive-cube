/*
 * $File: cube.cpp
 * $Date: Fri Dec 31 13:32:03 2010 +0800
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

	moving_axis = X;
	moving_slice = 0;
	moving_angle = 0;

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

	addStickers();
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
			foreach_cubie
				(*cubie)->addSticker(color[cnt], (Axis)i, location, Colorf(0, 0, 0), 0.1);
			cnt ++;
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

void Cubie::addSticker(const Colorf& color, Axis axis, int location, const Colorf &padding_color, GLfloat padding_relative_length)
{
	/*
	 * The cubie get a sticker on the face only if it is one the required face
	 */
	if (location - (location > 0 ? 1 : -1) != original_center[axis])
		return;
	
	Sticker *sticker = new Sticker();
	sticker->color = color;
	sticker->original_center = sticker->current_center = original_center;
	sticker->original_center[axis] = location;
	sticker->current_center[axis] = location;
	sticker->padding_color = padding_color;
	sticker->padding_relative_length = padding_relative_length;

	stickers.push_back(sticker);
}

bool Cubie::hasSticker()
{
	return !stickers.empty();
}

void Cube::drawCube(Renderer * renderer)
{
	GLfloat cube_size = 0.5;
	
	foreach_cubie
		if ((*cubie)->hasSticker())
			(*cubie)->drawCubie(renderer, cube_size, moving_axis, moving_slice, moving_angle);
}

void Cubie::drawCubie(Renderer * renderer, GLfloat size, Axis axis, int slice, int angle)
{
	/*
	 * Draw Cubie
	 */
	if (1)
	{
	renderer->pushMatrix();
	renderer->pushAttrib();

	GLfloat half_size = size * 0.5 * 0.99;

	Point center;
	for (int i = 0; i < N_AXES; i ++)
		center[i] = current_center[i] / 2.0 * size;

	if (angle != 0)
	{
		Point p;
		p[axis] = 1.0;
		renderer->rotateView(angle, p);
	}

	renderer->moveView(center);

	static Point vtxs[N_AXES * 2 * 4];
	int cnt = 0;
	for (int axis = 0; axis < N_AXES; axis ++)
	{
		for (int face = 0; face < 2; face ++)
		{
			Vector normal(0, 0, 0);
			normal[axis] = 2.0 * face - 1.0;
			renderer->setNormal(normal);
			Point p(0, 0, 0);
			p[axis] = (2.0 * face - 1.0) * half_size;
			int coord0, coord1;
			if (p[axis] > 0)
			{
				coord0 = axis + 2;
				coord1 = axis + 1;
			}
			else
			{
				coord0 = axis + 1;
				coord1 = axis + 2;
			}
			for (int i = 0; i < 2; i ++)
			{
				p[coord0] = (2 * i - 1) * half_size;
				for (int j = 0; j < 2; j ++)
				{
					int k = (i + j) % 2;
					p[coord1] = (2 * k - 1) * half_size;
					vtxs[cnt ++] = p;
				}
			}
		}
	}

	renderer->drawQuads(vtxs, cnt);

	renderer->popAttrib();
	renderer->popMatrix();
	}
	/*
	 * Draw Stickers
	 */
	if (1)
	foreach_sticker
	{
		Vector normal = (*sticker)->current_center - current_center;
		(*sticker)->drawSticker(renderer, size, normal);
	}
}

void Sticker::drawSticker(Renderer * renderer, GLfloat size, Vector &normal)
{
	renderer->pushMatrix();
	renderer->pushAttrib();

	Vector center = current_center / 2.0 * size;
	renderer->moveView(center);

	/*
	 * Draw the sticker
	 */
	renderer->setColor(color);
	renderer->setNormal(normal);

	GLfloat half_size = size * 0.5 * (1 - padding_relative_length);

	int axis0, axis1;
	for (int axis = 0; axis < N_AXES; axis ++)
		if (normal[axis] != 0)
		{
			center = normal * 0.01 * size;
			if (normal[axis] < 0)
			{
				axis0 = axis + 1;
				axis1 = axis + 2;
			}
			else
			{
				axis0 = axis + 2;
				axis1 = axis + 1;
			}
			Point p = center;
			static Point vtxs[4];
			int cnt = 0;
			for (int i = 0; i < 2; i ++)
			{
				p[axis0] = (i * 2 - 1) * half_size;
				for (int j = 0; j < 2; j ++)
				{
					int k = (i + j) % 2;
					p[axis1] = (k * 2 - 1) * half_size;
					vtxs[cnt ++] = p;
				}
			}
			renderer->drawQuad(vtxs);
		}

	/*
	 * Draw the padding
	 */
	// TODO
	renderer->popAttrib();
	renderer->popMatrix();
}

