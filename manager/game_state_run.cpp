/*
 * $File: game_state_run.cpp
 * $Date: Wed Dec 01 10:54:03 2010 +0800
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

#include "game_state_run.h"

GameStateRun::GameStateRun()
{
	eye_pos.set(0, 0, 0);
	normal_dir.set(0, 1, 0);
	cube_center.set(0, 0, -6);
	x_axis.set(1, 0, 0);
	y_axis.set(0, 1, 0);
	z_axis.set(0, 0, 1);
	cube_front_dir.set(0, 0, -1);
	cube_up_dir.set(0, 1, 0);
}

int GameStateRun::Init()
{
}
 
int GameStateRun::Idle()
{
}
 
int GameStateRun::Render()
{
	glLoadIdentity();
	gluLookAt(eye_pos.x, eye_pos.y, eye_pos.z,
			cube_center.x, cube_center.y, cube_center.z,
			normal_dir.x, normal_dir.y, normal_dir.z);

	if (keys['w'] || keys['W'])
		cube_center += Point(0, 0, 0.01);
	if (keys['s'] || keys['S'])
		cube_center -= Point(0, 0, 0.01);
	glTranslatef(cube_center.x, cube_center.y, cube_center.z);
	DrawCube();
}
 
int GameStateRun::Exit()
{
}

void GameStateRun::cbMouseEvent(int button, int state, int x, int y)
{
	mouse_button[button] = (state == MOUSE_DOWN ? true : false);
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbMousePassiveMotion(int x, int y)
{
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbMouseMotion(int x, int y)
{
	if (mouse_button[MOUSE_LEFT_BUTTON])
		doCubeRotate(x - mouse_x, y - mouse_y);
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbKeyPressed(unsigned char key, int x, int y)
{
	keys[key] = true;
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbKeyUp(unsigned char key, int x, int y)
{
	keys[key] = false;
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbSpecialKeyPressed(int key, int x, int y)
{
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::cbSpecialKeyUp(int key, int x, int y)
{
	mouse_x = x, mouse_y = y;
}
 
void GameStateRun::DrawCube(GLfloat len, const Point &center, const Color *colors)
{
		static Color default_colors[] = {
			Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1),
			Color(1, 1, 0), Color(1, 0, 1), Color(0, 1, 1)
		};
		if (colors == NULL)
			colors = default_colors;

		static Quad quads[] = {
			Quad(Point(0, 0, 1), Point(-1, -1, 1), Point(1, -1, 1), Point(1, 1, 1), Point(-1, 1, 1)),
			Quad(Point(0, 0, -1), Point(-1, -1, -1), Point(-1, 1, -1), Point(1, 1, -1), Point(1, -1, -1)),
			Quad(Point(0, 1, 0), Point(-1, 1, -1), Point(-1, 1, 1), Point(-1, 1, 1), Point(1, 1, -1)),
			Quad(Point(0, -1, 0), Point(-1, -1, -1), Point(1, -1, -1), Point(1, -1, 1), Point(-1, -1, 1)),
			Quad(Point(1, 0, 0), Point(1, -1, -1), Point(1, 1, -1), Point(1, 1, 1), Point(1, -1, 1)),
			Quad(Point(-1, 0, 0), Point(-1, -1, -1), Point(-1, -1, 1), Point(-1, 1, 1), Point(-1, 1, -1))
		};
		glBegin(GL_QUADS);
		for (int i = 0; i < 6; i ++)
		{
			Quad &quad = quads[i];
			glColor4f(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
			glNormal3f(quad.normal.x, quad.normal.y, quad.normal.z);
			for (int j = 0; j < 4; j ++)
				glVertex3f(quad.vtx[j].x * len, quad.vtx[j].y * len, quad.vtx[j].z * len);
		}
		glEnd();
		/*
		   glBegin(GL_QUADS);

		   glNormal3f( 0.0f, 0.0f, 1.0f);
		   glVertex3f(-1.0f, -1.0f,  1.0f);
		   glVertex3f( 1.0f, -1.0f,  1.0f);
		   glVertex3f( 1.0f,  1.0f,  1.0f);
		   glVertex3f(-1.0f,  1.0f,  1.0f);

		   glColor3f(0, 1, 0);
		   glNormal3f( 0.0f, 0.0f,-1.0f);
		   glVertex3f(-1.0f, -1.0f, -1.0f);
		   glVertex3f(-1.0f,  1.0f, -1.0f);
		   glVertex3f( 1.0f,  1.0f, -1.0f);
		   glVertex3f( 1.0f, -1.0f, -1.0f);

		   glColor3f(0, 0, 1);
		   glNormal3f( 0.0f, 1.0f, 0.0f);
		   glVertex3f(-1.0f,  1.0f, -1.0f);
		   glVertex3f(-1.0f,  1.0f,  1.0f);
		   glVertex3f( 1.0f,  1.0f,  1.0f);
		   glVertex3f( 1.0f,  1.0f, -1.0f);

		   glColor3f(1, 1, 0);
		   glNormal3f( 0.0f, -1.0f, 0.0f);
		   glVertex3f(-1.0f, -1.0f, -1.0f);
		   glVertex3f( 1.0f, -1.0f, -1.0f);
		   glVertex3f( 1.0f, -1.0f,  1.0f);
		   glVertex3f(-1.0f, -1.0f,  1.0f);

		   glColor3f(1, 0, 1);
		   glNormal3f( 1.0f, 0.0f, 0.0f);
		   glVertex3f( 1.0f, -1.0f, -1.0f);
		   glVertex3f( 1.0f,  1.0f, -1.0f);
		   glVertex3f( 1.0f,  1.0f,  1.0f);
		   glVertex3f( 1.0f, -1.0f,  1.0f);

		   glColor3f(0, 1, 1);
		   glNormal3f(-1.0f, 0.0f, 0.0f);
		   glVertex3f(-1.0f, -1.0f, -1.0f);
		   glVertex3f(-1.0f, -1.0f,  1.0f);
		   glVertex3f(-1.0f,  1.0f,  1.0f);
		   glVertex3f(-1.0f,  1.0f, -1.0f);

		   glEnd();
		   */
}

void GameStateRun::doCubeRotate(GLfloat x, GLfloat y)
{
	vector_rotate(cube_front_dir, y_axis, x);
	vector_rotate(cube_up_dir, y_axis, x);

	vector_rotate(cube_front_dir, x_axis, y);
	vector_rotate(cube_up_dir, x_axis, y);
#ifdef DEBUG
	printf("cube front dir: (%.3lf,%.3lf,%.3lf)\n", cube_front_dir.x, cube_front_dir.y, cube_front_dir.z);
	printf("cube up dir: (%.3lf,%.3lf,%.3lf)\n", cube_up_dir.x, cube_up_dir.y, cube_up_dir.z);
	printf("angle between front and up dir: %.3lf deg\n", get_angle(cube_front_dir, cube_up_dir));
#endif
}
