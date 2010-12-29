/*
 * $File: cube.h
 * $Date: Wed Dec 29 14:54:51 2010 +0800
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

#ifndef HEADER_CUBE
#define HEADER_CUBE

#include <list>
#include "header.h"
#include "math.h"
#include "color.h"
#include "renderer.h"

class Cubie;

/*
 * Here a cube consists of n * m * p "cubies". A cubie is a rectangular
 * parrellelpipied. All the cubies shaped the cube a rectangular parrellelpipied
 * too. In order to code easily, we make the gravity center of the cube
 * locate in (0,0,0), and all the cubies in size 2 * 2 * 2, thus the center
 * and faces of a cubie will be located in a integer coordinate. The absolute value
 * of one of the dimensions of one face of a cube gracefully equals the number
 * of cubies in that dimension. 
 */
class Cube
{
	public:
		Cube(int xlen = 3, int ylen = 3, int zlen = 3);
		~Cube();
		
		/*
		 * A slice can be determined by an axis and the location on that axis,
		 * where location is in range [-size[axis], +size[axis]].
		 * if a slice is not a square, the @direction will automatically
		 * change to ONE_EIGHTY.
		 */
		void moveSlice(Axis axis, int location, Rotation direction);

		/*
		 * Size of the Cube
		 */
		Point size;

		/*
		 * The list of cubies
		 */
		std::list<Cubie *> cubies;

		void drawCube(Renderer * renderer);

	private:

		Axis moving_axis;
		int moving_slice;
		int moving_angle;

		/*
		 * Delete all cubies
		 */
		void deleteCubies();

		/*
		 * Add stickers to every cubie
		 */
		void addStickers();
};

class Sticker
{
	public:
		Sticker();
		~Sticker();

		/*
		 * The color of this sticker
		 */
		Colorf color;

		Point current_center;
		Point original_center;

		void drawSticker(Renderer * renderer, GLfloat size, Vector &normal);
};

class Cubie
{
	public:
		Cubie(const Point &center);
		~Cubie();
		/*
		 * A axis and a location derminted a slice of a cube,
		 * pass these arguments to the function, and rotate 
		 * a single cubie
		 */
		void rotate(Axis axis, int location, Rotation direction);

		/*
		 * Add a sticker to one of the faces of a cubie
		 */
		void addSticker(const Colorf& color, Axis axis, int location);

		/*
		 * Whether this cubie has a sticker
		 */
		bool hasSticker();

		/*
		 * Draw cubie
		 */
		void drawCubie(Renderer * renderer, GLfloat size, Axis axis, int slice, int angle);

	private:
		Point original_center;
		Point current_center;

		/*
		 * The list of stickers
		 */
		std::list<Sticker *> stickers;
};

#endif // HEADER_CUBE
