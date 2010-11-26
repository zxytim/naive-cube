
#ifndef __INCLUDES_CUBE_MATH_H__
#define __INCLUDES_CUBE_MATH_H__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>

class Point
{
	public:
		GLfloat x, y, z;
		Point();
		Point(GLfloat _x, GLfloat _y, GLfloat _z);
		friend Point operator + (const Point &a, const Point &b);
		friend Point operator - (const Point &a, const Point &b);
		friend GLfloat operator * (const Point &a, const Point &b);
		friend Point operator * (const Point &a, GLfloat b);
		friend Point operator / (const Point &a, GLfloat b);
		friend Point CrossProduct(const Point &a, const Point &b);
		GLfloat mo() const;
		Point unit() const;

};
typedef Point Vector;

#endif // __INCLUDES_CUBE_MATH_H__
