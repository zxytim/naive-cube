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
