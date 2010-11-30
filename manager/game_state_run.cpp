#include "game_state_run.h"

GameStateRun::GameStateRun()
{
	eye_pos.set(0, 0, 0);
	normal_dir.set(0, 1, 0);
	cube_center.set(0, 0, -6);
}

void GameStateRun::Init()
{
}
 
void GameStateRun::Idle()
{
}
 
void GameStateRun::Render()
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
 
void GameStateRun::Exit()
{
}

void GameStateRun::cbMouseEvent(int button, int state, int x, int y)
{
}
 
void GameStateRun::cbMousePassiveMotion(int x, int y)
{
}
 
void GameStateRun::cbMouseMotion(int x, int y)
{
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
}
 
void GameStateRun::cbSpecialKeyUp(int key, int x, int y)
{
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
