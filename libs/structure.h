
#ifndef __CUBE_STRUCTURE_H__
#define __CUBE_STRUCTURE_H__

#include "math.h"
#include "color.h"

class CubeGrid
{
	public:
		Color color[6];
};

class Cube
{
	public:
		CubeGrid grid[3][3][3];
		bool is_completed();
		void rotate(int x, int y, int z, int axis);
};

class Quad
{
	public:
		Point normal;
		Point vtx[4];
		Quad();
		Quad(const Point &normal, const Point &v0, const Point &v1, const Point &v2, const Point &v3);
		// TODO
		//bool bind_texture;
};
#endif
