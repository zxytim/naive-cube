#include "cube_math.h"

#include <cmath>

Point::Point(){x = y = z = 0;}
Point::Point(GLfloat _x, GLfloat _y, GLfloat _z){x = _x, y = _y, z = _z;}
Point operator + (const Point &a, const Point &b)
{
	return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}
Point operator - (const Point &a, const Point &b)
{
	return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}
GLfloat operator * (const Point &a, const Point &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Point operator * (const Point &a, GLfloat b)
{
	return Point(a.x * b, a.y * b, a.z * b);
}
Point operator / (const Point &a, GLfloat b)
{
	return Point(a.x / b, a.y / b, a.z / b);
}
Point CrossProduct(const Point &a, const Point &b)
{
	return Point(a.y * b.z - a.z * b.y, a.x * b.z - a.z * b.x, a.x * b.y - a.y * b.x);
}
GLfloat Point::mo() const
{
	return sqrt(x * x + y * y + z * z);
}
Point Point::unit() const
{
	return Point(x, y, z) / mo();
}
