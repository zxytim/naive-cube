/*
 * $File: game_state_run.cpp
 * $Date: Thu Dec 02 20:02:52 2010 +0800
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

#include "game_state_run.h"

#ifdef DEBUG
#define DEBUG_POINT(p) printf(#p ": (%.3lf,%.3lf,%.3lf)\n", (p).x, (p).y, (p).z);
#endif

static GLfloat LightAmbient[] = {0.4f, 0.4f, 0.4f, 1.0f}; // 环境光
static GLfloat LightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f}; // 漫射光
static GLfloat LightPosition[] = {4.0f, 4.0f, 6.0f, 1.0f}; // 灯光的位置


GameStateRun::GameStateRun()
{
	eye_pos.set(0, 0, 0);
	eye_up_dir.set(0, 1, 0);
	cube_center.set(0, 0, -10);
	x_axis.set(1, 0, 0);
	y_axis.set(0, 1, 0);
	z_axis.set(0, 0, 1);
	cube_front_dir.set(0, 0, -1);
	cube_up_dir.set(0, 1, 0);
	eye_pos_move_sensitivity = 0.03;
	eye_pos_rotate_sensitivity = 0.2;
}

int GameStateRun::Init()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	return true;
}
 
int GameStateRun::Exit()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	return true;
}


int GameStateRun::Idle()
{
}

void GameStateRun::MoveEyePos(const Vector &dir)
{
	GLfloat dist = (eye_pos - cube_center).mo();
	eye_pos += dir;
	Vector d = eye_pos - cube_center;
	d = d.resize(dist);
	eye_pos = cube_center + d;
#ifdef DEBUG
	printf("----------------\n");
	printf("dist: %.3lf\n", dist);
	printf("d: %.3lf\n", d.mo());
	printf("real: %.3lf\n", (eye_pos - cube_center).mo());
#endif
	d = cube_center - eye_pos;
	eye_up_dir = CrossProduct(CrossProduct(eye_up_dir, d), d).unit() * -1;
	LightPosition[0] = eye_pos.x;
	LightPosition[1] = eye_pos.y;
	LightPosition[2] = eye_pos.z;
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
#ifdef DEBUG
	DEBUG_POINT(eye_up_dir);
#endif
}

int GameStateRun::Render()
{
	glClearColor(0.5, 0.5, 0.5, 0.5);
	glLoadIdentity();
	Point eye_sight_pos = eye_pos + (cube_center - eye_pos).resize((cube_center - eye_pos).mo() * 1.5);
	gluLookAt(eye_pos.x, eye_pos.y, eye_pos.z,
			eye_sight_pos.x, eye_sight_pos.y, eye_sight_pos.z,
			eye_up_dir.x, eye_up_dir.y, eye_up_dir.z);

	if (keys['w'] || keys['W'])
		MoveEyePos(eye_up_dir.resize(eye_pos_rotate_sensitivity));
	if (keys['s'] || keys['S'])
		MoveEyePos(eye_up_dir.resize(eye_pos_rotate_sensitivity) * -1);
	if (keys['a'] || keys['A'])
		MoveEyePos(CrossProduct(eye_pos - cube_center, eye_up_dir).resize(eye_pos_rotate_sensitivity));
	if (keys['d'] || keys['D'])
		MoveEyePos(CrossProduct(cube_center - eye_pos, eye_up_dir).resize(eye_pos_rotate_sensitivity));

	glTranslatef(cube_center.x, cube_center.y, cube_center.z);

	DrawMagicCube();
//	DrawCube();
}

void GameStateRun::cbMouseEvent(int button, int state, int x, int y)
{
	mouse_button[button] = (state == MOUSE_DOWN);
	mouse_x = x, mouse_y = y;

	if (mouse_button[MOUSE_LEFT_BUTTON])
	{
		// ---- selection -----

		GLint viewport[4];
		const int BUF_SIZE = 1000;
		GLuint buffer[BUF_SIZE];

		// viewport: [0] x, [1] y, [2] length, [3] width
		glGetIntegerv(GL_VIEWPORT, viewport);
		glSelectBuffer(BUF_SIZE, buffer);

		glRenderMode(GL_SELECT);

		glInitNames();
		glPushName(0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		gluPickMatrix((GLdouble)mouse_x, (GLdouble)(viewport[3] - mouse_y),
				1.0f, 1.0f, viewport);

		gluPerspective(45.0f, (GLfloat)(viewport[2] - viewport[0]) / (GLfloat)(viewport[3] - viewport[1]), 0.1, 100.0f);
		glMatrixMode(GL_MODELVIEW);

		DrawMagicCube();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		int hits = glRenderMode(GL_RENDER);
#ifdef DEBUG
		if (hits)
		{
			printf("hits: %d\n", hits);
			for (int i = 0; i < 4; i ++)
				printf("%d ", buffer[i]);
			printf("\n");
		}
#endif
	}
}

void GameStateRun::cbMousePassiveMotion(int x, int y)
{
	mouse_x = x, mouse_y = y;
}

void GameStateRun::cbMouseMotion(int x, int y)
{
	if (mouse_button[MOUSE_RIGHT_BUTTON])
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
	spkeys[key] = true;
	mouse_x = x, mouse_y = y;
}

void GameStateRun::cbSpecialKeyUp(int key, int x, int y)
{
	spkeys[key] = false;
	mouse_x = x, mouse_y = y;
}

void GameStateRun::DrawMagicCube()
{
	for (int i = 0; i < 3; i ++)
		for (int j = 0; j < 3; j ++)
			for (int k = 0; k < 3; k ++)
			{
				if (!(i == 1 && j == 1 && k == 1))
				glLoadName(i * 9 + j * 3 + k);
				DrawCube(1, Point(i - 1, j - 1, k - 1));
			}
}

void GameStateRun::DrawQuad(const Point a, const Point b, const Point c, const Point d)
{
#define DRAW(a) glVertex3f(a.x, a.y, a.z)
	DRAW(a); DRAW(b); DRAW(c); DRAW(d);
#undef DRAW
}

void GameStateRun::DrawCube(GLfloat len, const Point &center, const Colorf *colors, GLfloat padding, const Colorf &padding_color)
{
	GLfloat half_len = len * 0.5;
	AdjustRange(padding, 0.0f, half_len);
	static Colorf default_colors[6] = {
		Colorf(1, 0, 0), Colorf(0, 1, 0), Colorf(0, 0, 1),
		Colorf(1, 1, 0), Colorf(1, 0, 1), Colorf(0, 1, 1)
	};
	if (colors == NULL)
		colors = default_colors;

	static Quad quads[] = {
		// front
		Quad(Point(0, 0, 1), Point(-1, -1, 1), Point(1, -1, 1), Point(1, 1, 1), Point(-1, 1, 1)),
		// back
		Quad(Point(0, 0, -1), Point(-1, -1, -1), Point(-1, 1, -1), Point(1, 1, -1), Point(1, -1, -1)),
		// top
		Quad(Point(0, 1, 0), Point(-1, 1, -1), Point(-1, 1, 1), Point(1, 1, 1), Point(1, 1, -1)),
		// bottom
		Quad(Point(0, -1, 0), Point(-1, -1, -1), Point(1, -1, -1), Point(1, -1, 1), Point(-1, -1, 1)),
		// right
		Quad(Point(1, 0, 0), Point(1, -1, -1), Point(1, 1, -1), Point(1, 1, 1), Point(1, -1, 1)),
		// left
		Quad(Point(-1, 0, 0), Point(-1, -1, -1), Point(-1, -1, 1), Point(-1, 1, 1), Point(-1, 1, -1))
	};

	glPushMatrix();

	glTranslatef(center.x, center.y, center.z);
	for (int i = 0; i < 6; i ++)
	{
		glBegin(GL_QUADS);
		Quad &quad = quads[i];
		Point *vtx = quad.vtx;
		glNormal3f(quad.normal.x, quad.normal.y, quad.normal.z);
		bool same_x = true, same_y = true, same_z = true;
		for (int j = 1; j < 4; j ++)
		{
			same_x &= vtx[j].x == vtx[j - 1].x;
			same_y &= vtx[j].y == vtx[j - 1].y;
			same_z &= vtx[j].z == vtx[j - 1].z;
		}
		// draw padding
		glColor4f(padding_color.r, padding_color.g, padding_color.b, padding_color.a);
		Vector dir03 = (vtx[3] - vtx[0]).unit(), dir01 = (vtx[1] - vtx[0]).unit();
		Point O = vtx[0] + (vtx[2] - vtx[0]) * 0.5;
#define TRANS(p) (p * len * 0.5)
		Point v0 = TRANS(vtx[0]), v1 = TRANS(vtx[1]),
			  v2 = TRANS(vtx[2]), v3 = TRANS(vtx[3]);
#undef TRANS
		DrawQuad(v0, v1, v1 + dir03 * padding, v0 + dir03 * padding);
		DrawQuad(v2, v3, v3 - dir03 * padding, v2 - dir03 * padding);
		DrawQuad(v0 + dir03 * padding, v3 - dir03 * padding,
				v3 - (dir03 - dir01) * padding, v0 + (dir03 + dir01) * padding);
				
		DrawQuad(v1 + dir03 * padding, v2 - dir03 * padding,
				v2 - (dir03 + dir01) * padding, v1 + (dir03 - dir01) * padding);
		// draw center
		glColor4f(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
		for (int j = 0; j < 4; j ++)
		{
			glVertex3f(vtx[j].x * (half_len - (!same_x) * padding), 
					vtx[j].y * (half_len - (!same_y) * padding), 
					vtx[j].z * (half_len - (!same_z) * padding));
		}
		glEnd();
	}
	glPopMatrix();
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
