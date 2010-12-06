/*
 * $File: renderer.cpp
 * $Date: Mon Dec 06 18:16:03 2010 +0800
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

	glutInitDisplayMode(GLUT_ALPHA | GLUT_RGBA | GLUT_DEPTH);

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

