/*
 * $File: structure.cpp
 * $Date: Fri Dec 03 11:07:39 2010 +0800
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
#include "structure.h"
#include <cstring>
#include "common.h"

// grid id
#define GID(x, y, z) ((x) * size * size + (y) * size + (z))


Quad::Quad(const Point &normalv, const Point &v0, const Point &v1, const Point &v2, const Point &v3)
{
	normal = normalv;
	vtx[0] = v0;
	vtx[1] = v1;
	vtx[2] = v2;
	vtx[3] = v3;
}

void Cube::CubeGrid::set_default(int id_, const Point &center_)
{
	static Colorf default_colors[6] = {
		Colorf(1, 0, 0), Colorf(0, 1, 0), Colorf(0, 0, 1),
		Colorf(1, 1, 0), Colorf(1, 0, 1), Colorf(0, 1, 1)
	};
	memcpy(color, default_colors, sizeof(color));
	center = center_;
	for (int i = 0; i < 6; i ++)
		visibility[i] = true;
	id = id_;
}

void Cube::set_default(int size_, GLfloat len, GLfloat padding_, const Colorf &padding_color_)
{
	size = size_;
	if (grid != NULL)
	{
		delete[] grid;
		grid = NULL;
	}
	grid = new CubeGrid[size * size * size];
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++)
			for (int k = 0; k < size; k ++)
				grid[GID(i, j, k)].set_default(GID(i, j, k),
					   	Point(i - (size - 1) * 0.5, j - (size - 1) * 0.5, k - (size - 1) * 0.5));
	grid_len = len;
	padding = padding_;
	padding_color = padding_color_;
}

void Cube::reset()
{
	memset(grid, 0, sizeof(CubeGrid) * size * size * size);
	grid_len = 1;
}

Cube::Cube(int size, GLfloat len, GLfloat padding, const Colorf &padding_color)
{
	grid = NULL;
	set_default(size, len, padding, padding_color);
}

void Cube::draw(const Point &center) const
{
	for (int i = 0; i < size; i ++)
		for (int j = 0; j < size; j ++)
			for (int k = 0; k < size; k ++)
				grid[GID(i, j, k)].draw(grid_len, padding, padding_color);
}

void DrawQuad(const Point &a, const Point &b, const Point &c, const Point &d)
{
#define DRAW(a) glVertex3f(a.x, a.y, a.z)
	DRAW(a); DRAW(b); DRAW(c); DRAW(d);
#undef DRAW
}

void Cube::CubeGrid::draw(GLfloat len, GLfloat padding, const Colorf &padding_color) const
{
	glLoadName(id);
	GLfloat half_len = len * 0.5;
	AdjustRange(padding, 0.0f, half_len);
	static Quad quads[] = {
		// front
		Quad(Point(0, 0, 1), Point(-1, -1, 1), Point(1, -1, 1), Point(1, 1, 1), Point(-1, 1, 1)),
		// back
		Quad(Point(0, 0, -1), Point(-1, -1, -1), Point(-1, 1, -1), Point(1, 1, -1), Point(1, -1, -1)),
		// top
		Quad(Point(0, 1, 0), Point(-1, 1, -1), Point(-1, 1, 1), Point(1, 1, 1), Point(1, 1, -1)),
		// bottom
		Quad(Point(0, -1, 0), Point(-1, -1, -1), Point(1, -1, -1), Point(1, -1, 1), Point(-1, -1, 1)),
		// right
		Quad(Point(1, 0, 0), Point(1, -1, -1), Point(1, 1, -1), Point(1, 1, 1), Point(1, -1, 1)),
		// left
		Quad(Point(-1, 0, 0), Point(-1, -1, -1), Point(-1, -1, 1), Point(-1, 1, 1), Point(-1, 1, -1))
	};

	glPushMatrix();

	glTranslatef(center.x, center.y, center.z);
	for (int i = 0; i < 6; i ++)
	{
		glBegin(GL_QUADS);
		Quad &quad = quads[i];
		Point *vtx = quad.vtx;
		glNormal3f(quad.normal.x, quad.normal.y, quad.normal.z);
		bool same_x = true, same_y = true, same_z = true;
		for (int j = 1; j < 4; j ++)
		{
			same_x &= vtx[j].x == vtx[j - 1].x;
			same_y &= vtx[j].y == vtx[j - 1].y;
			same_z &= vtx[j].z == vtx[j - 1].z;
		}
		// draw padding
		glColor4f(padding_color.r, padding_color.g, padding_color.b, padding_color.a);
		Vector dir03 = (vtx[3] - vtx[0]).unit(), dir01 = (vtx[1] - vtx[0]).unit();
		Point O = vtx[0] + (vtx[2] - vtx[0]) * 0.5;
#define TRANS(p) (p * len * 0.5)
		Point v0 = TRANS(vtx[0]), v1 = TRANS(vtx[1]),
			  v2 = TRANS(vtx[2]), v3 = TRANS(vtx[3]);
#undef TRANS
		DrawQuad(v0, v1, v1 + dir03 * padding, v0 + dir03 * padding);
		DrawQuad(v2, v3, v3 - dir03 * padding, v2 - dir03 * padding);
		DrawQuad(v0 + dir03 * padding, v3 - dir03 * padding,
				v3 - (dir03 - dir01) * padding, v0 + (dir03 + dir01) * padding);

		DrawQuad(v1 + dir03 * padding, v2 - dir03 * padding,
				v2 - (dir03 + dir01) * padding, v1 + (dir03 - dir01) * padding);
		// draw center
		glColor4f(color[i].r, color[i].g, color[i].b, color[i].a);
		for (int j = 0; j < 4; j ++)
		{
			glVertex3f(vtx[j].x * (half_len - (!same_x) * padding), 
					vtx[j].y * (half_len - (!same_y) * padding), 
					vtx[j].z * (half_len - (!same_z) * padding));
		}
		glEnd();
	}
	glPopMatrix();

}

