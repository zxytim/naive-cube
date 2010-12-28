/*
 * $File: cube_view.h
 * $Date: Tue Dec 28 10:47:41 2010 +0800
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

#ifndef HEADER_CUBE_VIEW
#define HEADER_CUBE_VIEW

#include "header.h"
#include "math.h"
#include <GL/gl.h>

class CubeView
{
	public:
		CubeView();
		~CubeView();
		/*
		 * whether this one will show on screen
		 */
		bool visible;
		GLfloat cube_size;
		/*
		 * The relative coordinate on the screen,
		 * float in range 0 to 1
		 */
		GLfloat relative_x, relative_y; 

		Point position;
		/*
		 * With turn and tilt, make 3 faces visible in the begining
		 */
		GLfloat turn,  // Angle around Y-axis
				tilt;  
};

#endif // HEADER_CUBE_VIEW
