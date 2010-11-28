
#ifndef __CUBE_STRUCTURE_H__
#define __CUBE_STRUCTURE_H__

#include "cube_math.h"

class CubeGrid
{
	public:
		int color[6];
};

class Cube
{
	public:
		CubeGrid grid[3][3][3];
		bool is_completed();
		void rotate(int x, int y, int z, int axis);
};

#endif
