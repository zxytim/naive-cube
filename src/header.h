/*
 * $File: header.h
 * $Date: Tue Dec 28 10:51:52 2010 +0800
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

#ifndef HEADER_GENERAL
#define HEADER_GENERAL

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

#define GAME_NAME "naive-cube"

const int WINDOW_WIDTH_DEFAULT					= 800;
const int WINDOW_HEIGHT_DEFAULT					= 600;
const GLfloat CUBE_CENTER_Z						= -6.0;

enum Axis {X, Y, Z, N_AXES};
enum Rotation {CLOCKWISE, ANTICLOCKWISE, ONE_EIGHTY};


#include "exception.h"
#include "common.h"
#include "log.h"

#endif // HEADER_GENERAL
