/*
 * $File: renderer.cpp
 * $Date: Fri Dec 31 13:53:44 2010 +0800
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

#include "header.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "renderer.h"
#include "math.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

Renderer* Renderer::instance()
{
	static Renderer renderer;
	return &renderer;
}

void Renderer::init(int argc, char *argv[], const char * window_name, int width, int height)
{
	window_width = width;

	window_height = height;

	/*
	 * Initialize display
	 */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_ALPHA);

	glutInitWindowSize(window_width, window_height);

	glutInitWindowPosition(0, 0);

	window = glutCreateWindow(window_name);


	/*
	 * OpenGL settings
	 */
	glClearColor(0, 0, 0, 0);

	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);

	gluPerspective(VIEW_ANGLE, (GLfloat)window_width / (GLfloat)window_height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}


void Renderer::setBackgroundColor(const Colorf &color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::reshape(int width, int height)
{
	if (height == 0)
		height = 1;
	
	window_width = width;
	window_height = height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	
	gluPerspective(VIEW_ANGLE, (GLfloat)width / (GLfloat)height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void Renderer::beginRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
}

void Renderer::endRender()
{
	glutSwapBuffers();
}

void Renderer::moveView(GLfloat x_change, GLfloat y_change, GLfloat z_change)
{
	glTranslatef(x_change, y_change, z_change);
}

void Renderer::moveView(const Point &dir)
{
	glTranslatef(dir.x, dir.y, dir.z);
}

void Renderer::rotateView(GLfloat degree, GLfloat x, GLfloat y, GLfloat z)
{
	glRotatef(degree, x, y, z);
}

void Renderer::rotateView(GLfloat degree, const Vector &axis)
{
	glRotatef(degree, axis.x, axis.y, axis.z);
}

void Renderer::drawVertex(GLfloat x, GLfloat y, GLfloat z)
{
	glVertex3f(x, y, z);
}

void Renderer::drawVertex(const Point &p)
{
	glVertex3f(p.x, p.y, p.z);
}

void Renderer::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glColor4f(r, g, b, a);
}

void Renderer::setColor(const Colorf &color)
{
	glColor4f(color.r, color.g, color.b, color.a);
}

void Renderer::drawLine(const Point &a, const Point &b)
{
	glBegin(GL_LINES);
	glVertex3f(a.x, a.y, a.z);
	glVertex3f(b.x, b.y, b.z);
	glEnd();
}

void Renderer::drawLines(const Point *vtxs, int n)
{
	glBegin(GL_LINES);
	for (int i = 0; i < n; i ++)
		glVertex3f(vtxs[i].x, vtxs[i].y, vtxs[i].z);
	glEnd();
}

void Renderer::drawLineStrip(const Point *vtxs, int n)
{
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < n; i ++)
		glVertex3f(vtxs[i].x, vtxs[i].y, vtxs[i].z);
	glEnd();
}

void Renderer::drawLineLoop(const Point *vtxs, int n)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; i ++)
		glVertex3f(vtxs[i].x, vtxs[i].y, vtxs[i].z);
	glEnd();
}

void Renderer::drawQuad(const Point &v0, const Point &v1, const Point &v2, const Point &v3)
{
	glBegin(GL_QUADS);

	glVertex3f(v0.x, v0.y, v0.z);
	glVertex3f(v1.x, v1.y, v1.z);
	glVertex3f(v2.x, v2.y, v2.z);
	glVertex3f(v3.x, v3.y, v3.z);

	glEnd();
}

void Renderer::drawQuad(const Point *vtxs)
{
	glBegin(GL_QUADS);

	for (int i = 0; i < 4; i ++)
		glVertex3f(vtxs[i].x, vtxs[i].y, vtxs[i].z);

	glEnd();
}

void Renderer::drawQuads(const Point *vtxs, int n)
{
	glBegin(GL_QUADS);

	for (int i = 0; i < n; i ++)
		glVertex3f(vtxs[i].x, vtxs[i].y, vtxs[i].z);

	glEnd();
}


void Renderer::setNormal(const Vector &normal)
{
	glNormal3f(normal.x, normal.y, normal.z);
}

void Renderer::setNormal(GLfloat x, GLfloat y, GLfloat z)
{
	glNormal3f(x, y, z);
}

void setNormal(GLfloat x, GLfloat y, GLfloat z);


void Renderer::pushMatrix()
{
	glPushMatrix();
}

void Renderer::popMatrix()
{
	glPopMatrix();
}

void Renderer::pushAttrib(unsigned int attrib)
{
	glPushAttrib(attrib);
}

void Renderer::popAttrib()
{
	glPopAttrib();
}

/*
 * Attributes
 */
int Renderer::width()
{
	return window_width;
}

int Renderer::height()
{
	return window_height;
}

