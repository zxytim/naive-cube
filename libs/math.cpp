#include "math.h"

#include <cmath>

#ifndef EPS
#define EPS 1e-7
#endif

Point::Point(){x = y = z = 0;}
Point::Point(GLfloat _x, GLfloat _y, GLfloat _z){x = _x, y = _y, z = _z;}

void Point::set(GLfloat _x, GLfloat _y, GLfloat _z){x = _x, y = _y, z = _z;}

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

bool operator == (const Point &a, const Point &b)
{
	return fabs(a.x - b.x) < EPS && fabs(a.y - b.y) < EPS && fabs(a.z - b.z) < EPS;
}

bool operator != (const Point &a, const Point &b)
{
	return fabs(a.x - b.x) >= EPS || fabs(a.y - b.y) >= EPS || fabs(a.z - b.z) >= EPS;
}

Point CrossProduct(const Point &a, const Point &b)
{
	return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
GLfloat Point::mo() const
{
	return sqrt(x * x + y * y + z * z);
}
Point Point::unit() const
{
	return Point(x, y, z) / mo();
}
Point Point::resize(GLfloat len) const
{
	return (*this) / mo() * len;
}

bool Point::is_zero() const
{
	return fabs(x) < EPS && fabs(y) < EPS && fabs(z) < EPS;
}

Point Point::rotate(Point vec, GLfloat angle)
{
	vec = vec.unit();
	Point c = vec * ((*this) * vec);
	Point vert = (*this) - c;
	if (vert.is_zero()) return *this;
	GLfloat len = vert.mo();
	vert = vert.unit();
	Point t = CrossProduct(vert, vec);
	angle = angle / 180.0 * PI;
	return (vert * cos(angle) + t * sin(angle)) * len + c;
}

GLfloat Point::get_angle(const Point &v) const
{
	return acos((*this) * v / (mo() * v.mo())) / PI * 180;
}

GLfloat get_angle(const Point &a, const Point &b)
{
	return a.get_angle(b);
}


void vector_rotate(Point &vec, const Point &axis, GLfloat angle)
{
	vec = vec.rotate(axis, angle);
}

Point& Point::operator += (const Point &a)
{
	(*this).x += a.x;
	(*this).y += a.y;
	(*this).z += a.z;
	return *this;
}

Point& Point::operator -= (const Point &a)
{
	(*this).x -= a.x;
	(*this).y -= a.y;
	(*this).z -= a.z;
	return *this;
}

Point& Point::operator *= (GLfloat factor)
{
	(*this).x *= factor;
	(*this).y *= factor;
	(*this).z *= factor;
	return (*this);
}

Point& Point::operator /= (GLfloat factor)
{
	(*this).x /= factor;
	(*this).y /= factor;
	(*this).z /= factor;
	return (*this);
}

