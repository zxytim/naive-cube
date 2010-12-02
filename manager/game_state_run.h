/*
 * $File: game_state_run.h
 * $Date: Thu Dec 02 11:25:43 2010 +0800
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
   along with JKOS.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __GAME_STATE_RUN_H__
#define __GAME_STATE_RUN_H__

#include "manager.h"
#include "../cube.h"

class GameStateRun : public GameState
{
	private:
		DECLARE_GAME_STATE_CLASS_DEFAULT_MEMBER_FUNCTION(Run);
		void DrawCube(GLfloat len = 1, const Point &center = Point(0, 0, 0), const Color *colors = NULL);
		void DrawMagicCube();
		void doCubeRotate(GLfloat x, GLfloat y);
		Point eye_pos,
			  eye_up_dir,
			  cube_center,
			  cube_front_dir,
			  cube_up_dir,
			  x_axis, y_axis, z_axis;
		bool keys[256];
		bool spkeys[256];
		bool mouse_button[3];
		int mouse_x, mouse_y;
		GLfloat eye_pos_move_sensitivity;
		GLfloat eye_pos_rotate_sensitivity;
		void MoveEyePos(const Vector &dir);
		static const GLfloat CUBE_DIST_MIN = 5;
		static const GLfloat CUBE_DIST_MAX = 7;
};

#endif // __GAME_STATE_MENU_H__
