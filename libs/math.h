
#ifndef __LIBS_CUBE_MATH_H__
#define __LIBS_CUBE_MATH_H__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>

#define PI 3.141592653589793236
#define EPS 1e-7

class Point
{
	public:
		GLfloat x, y, z;
		Point();
		Point(GLfloat x, GLfloat y, GLfloat z);
		void set(GLfloat x, GLfloat y, GLfloat z);
		friend Point operator + (const Point &a, const Point &b);
		friend Point operator - (const Point &a, const Point &b);
		friend GLfloat operator * (const Point &a, const Point &b);
		friend Point operator * (const Point &a, GLfloat factor);
		friend Point operator / (const Point &a, GLfloat factor);
		friend bool operator == (const Point &a, const Point &b);
		friend bool operator != (const Point &a, const Point &b);
		Point& operator += (const Point &a);
		Point& operator -= (const Point &a);
		Point& operator *= (GLfloat factor);
		Point& operator /= (GLfloat factor);
		friend Point CrossProduct(const Point &a, const Point &b);
		GLfloat mo() const;
		Point unit() const;
		bool is_zero() const;
		Point resize(GLfloat len) const;
		Point rotate(Point axis, GLfloat angle);
		friend void vector_rotate(Point &vec, const Point &axis, GLfloat angle);
		GLfloat get_angle(const Point &v) const;
		friend GLfloat get_angle(const Point &a, const Point &b);
};

typedef Point Vector;

#endif // __LIBS_CUBE_MATH_H__
