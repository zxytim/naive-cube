/*
 * $File: header.h
 * $Date: Mon Dec 06 20:36:26 2010 +0800
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

#ifdef __WIN32__
#include <windows.h>
#endif

#define GAME_NAME "naive-cube"

#define WINDOW_WIDTH_DEFAULT					800
#define WINDOW_HEIGHT_DEFAULT					600

enum Axis {X, Y, Z, N_AXIS};
enum Rotation {CLOCKWISE, ANTICLOCKWISE, ONE_EIGHTY};


#include "exception.h"
#include "common.h"

#endif // HEADER_GENERAL
