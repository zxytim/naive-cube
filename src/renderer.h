/*
 * $File: renderer.h
 * $Date: Mon Dec 06 18:55:18 2010 +0800
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

#define VIEW_ANGLE			30

#include "color.h"
#include "math.h"

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
		void moveView(GLfloat x_change, GLfloat y_change, GLfloat z_change);
		void moveView(const Point &dir);

		void rotateView(GLfloat degree, GLfloat x, GLfloat y, GLfloat z);
		void rotateView(GLfloat degree, const Vector &axis);
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

