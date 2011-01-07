/*
 * $File: renderer.h
 * $Date: Thu Dec 30 21:26:58 2010 +0800
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

#ifndef HEADER_RENDERER
#define HEADER_RENDERER

#include "header.h"
#include <GL/gl.h>

#include "color.h"
#include "math.h"

const GLfloat VIEW_ANGLE = 30.0;

class Renderer
{
	public:
		/*
		 * The only instance
		 */
		static Renderer *instance();

		/*
		 * Initialize the renderer, must be called first
		 */
		void init(int argc, char *argv[], const char *window_name, int width, int height);

		/*
		 * Set the background color
		 */
		void setBackgroundColor(const Colorf &color);

		/*
		 * Reshape the window
		 */
		void reshape(int width, int height);

		/*
		 * Initializing and finalizing the render
		 */
		void beginRender();
		void endRender();

		/*
		 * Operations
		 */
		void pushMatrix();
		void popMatrix();

		void pushAttrib(unsigned int attrib = GL_ALL_ATTRIB_BITS);
		void popAttrib();

		void moveView(GLfloat x_change, GLfloat y_change, GLfloat z_change);
		void moveView(const Point &dir);

		void rotateView(GLfloat degree, GLfloat x, GLfloat y, GLfloat z);
		void rotateView(GLfloat degree, const Vector &axis);

		void drawVertex(GLfloat x, GLfloat y, GLfloat z);
		void drawVertex(const Point &p);

		void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1);
		void setColor(const Colorf &color);

		void drawLine(const Point &a, const Point &b);

		/*
		 * This function draw consecutive lines with shared vertices,
		 * every consecutive 2 vertices is a line
		 * parameter n is the number of vertices
		 * n - 1 lines are drawn
		 */
		void drawLineStrip(const Point *vtxs, int n);

		/*
		 * This function draw separate lines. Every pair of vertices
		 * defines a line, that is: vtxs[0] and vtxs[1] make a line,
		 * vtxs[2] and vtxs[3] make a line.
		 * parameter n is the number of vertices 
		 * n / 2 lines are drawn
		 */
		void drawLines(const Point *vtxs, int n);
		
		/*
		 * This function draw connected lines from the first to last,
		 * then back to first
		 * n lines are drawn
		 */
		void drawLineLoop(const Point *vtxs, int n);

		void drawQuad(const Point &v0, const Point &v1, const Point &v2, const Point &v3);
		void drawQuad(const Point *vtxs);
		/*
		 * Draw Quads 4 vertices a group.
		 * n is the number of vertices, the remaining vertices are
		 * invalidated.
		 */
		void drawQuads(const Point *vtxs, int n);

		void setNormal(const Vector &normal);
		void setNormal(GLfloat x, GLfloat y, GLfloat z);
		/*
		 * Attributes
		 */
		int width();
		int height();

	private:
		/*
		 * The handle of window
		 */
		int window;

		/*
		 * Private constructor and distructor prevent the class from
		 * a second instance.
		 */
		Renderer();
		~Renderer();

		/*
		 * The width and height of the window
		 */
		int window_width, window_height;

		/*
		 * The fullscreen flag
		 */
		bool fullscreen;
};
#endif // HEADER_RENDERER
