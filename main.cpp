/*
 * $File: main.cpp
 * $Date: Wed Dec 01 10:54:27 2010 +0800
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

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include <unistd.h>
#include <cstdio>
#include <cmath>

#include "cube.h"
#include "manager/manager.h"

#define GAME_NAME "Naive Cube"

/* --------- Structures --------- */
typedef void (*GameStateCallback)();
typedef void (*MouseMotionCallback)(int, int);
typedef void (*KeyPressedCallback)(unsigned char, int, int);

/* ---------- Consts ------------ */
const Vector x_axis(1, 0, 0),
	  y_axis(0, 1, 0),
	  z_axis(0, 0, -1);

/* --------- Variables ---------- */
// Game manager
GameManager *GM = GameManagerInstance();
// settings
GLfloat mouse_sensitivity = 0.12;

// game
int game_state					= GAME_STATE_RUN,
	FPS							= 60;

// cube and observer
GLfloat observer_sight_len = 100.0;
Vector cube_pos					= Point(0, 0, -6),
	   cube_front_dir			= z_axis,
	   cube_up_dir				= y_axis,

	   observer_pos				= Point(0, 0, 0),
	   observer_front_dir		= z_axis * observer_sight_len,
	   observer_up_dir			= y_axis;

// window
int window_width				= 800,
	window_height				= 600,
	window;

// color
Color background_color			= Color(0, 0, 0, 0);

// mouse state
bool mouse_pressed[3];		// MOUSE_LEFT_BUTTON, MOUSE_MIDDLE_BUTTON, MOUSE_RIGHT_BUTTON
int mouse_x, mouse_y;


/* -------- Function declarations ---------- */
void doCubeRotate(GLfloat x, GLfloat y);
void InitConfig();
void InitGameMananger();
void InitGL(int argc, char *argv[]);

// callbacks
// OpenGL callbacks
GLvoid cbDrawScene();
GLvoid cbIdle();
GLvoid cbReshape(int width, int height);
GLvoid cbKeyPressed(unsigned char key, int x, int y);
GLvoid cbKeyUp(unsigned char key, int x, int y);
GLvoid cbSpecialKeyPressed(int key, int x, int y);
GLvoid cbSpecialKeyUp(int key, int x, int y);
GLvoid cbMouseEvent(int button, int state, int x, int y);
GLvoid cbMouseMotion(int x, int y);
GLvoid cbMousePassiveMotion(int x, int y);

/* ================================================ */

int main(int argc, char *argv[])
{
	InitConfig();

	InitGameMananger();

	InitGL(argc, argv);

	glutMainLoop();

	return 0;
}



void InitConfig()
{
}

void InitGameMananger()
{
	GM->RegisterGameStateInstance(GAME_STATE_RUN, GameStateRun::GetInstance());
	GM->ChangeState(GAME_STATE_RUN);
}


void InitGL(int argc, char *argv[])
{
	/* window settings */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_ALPHA | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(window_width, window_height);

	glutInitWindowPosition(0, 0);

	window = glutCreateWindow(GAME_NAME);


	/* display settings */
	glutDisplayFunc(cbDrawScene);

	glutIdleFunc(cbIdle);

	glutReshapeFunc(cbReshape);

	/* keyboard event callbacks */
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glutKeyboardFunc(cbKeyPressed);

	glutKeyboardUpFunc(cbKeyUp);

	glutSpecialFunc(cbSpecialKeyPressed);

	glutSpecialUpFunc(cbSpecialKeyUp);

	/* mouse event callbacks */
	glutMouseFunc(cbMouseEvent);

	glutMotionFunc(cbMouseMotion);

	glutPassiveMotionFunc(cbMousePassiveMotion);



	glClearColor(background_color.r, background_color.g, background_color.g, background_color.a);

	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);

	gluPerspective(45.0, (GLfloat)window_width / (GLfloat)window_height, 0.1, 100.0);
}



GLvoid cbDrawScene()
{
	GM->Render();

	return;
}

GLvoid cbIdle()
{
	if (timeEnd(TIME_UNIT_MS) * FPS < 1000)
	{
		usleep(1000 / FPS / 2);
		return;
	}

	GM->Idle();

	timeStart();
}


GLvoid cbReshape(int width, int height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid cbKeyPressed(unsigned char key, int x, int y)
{
	mouse_x = x, mouse_y = y;
	GM->cbKeyPressed(key, x, y);
	/*
	   if (key == KEY_ESCAPE)
	   {
	   glutDestroyWindow(window);
	   exit(0);
	   }
	   */
}

GLvoid cbKeyUp(unsigned char key, int x, int y)
{
	GM->cbKeyUp(key, x, y);
}

GLvoid cbSpecialKeyPressed(int key, int x, int y)
{
	GM->cbSpecialKeyPressed(key, x, y);
}

GLvoid cbSpecialKeyUp(int key, int x, int y)
{
	GM->cbSpecialKeyUp(key, x, y);
}

GLvoid cbMouseEvent(int button, int state, int x, int y)
{
	GM->cbMouseEvent(button, state, x, y);
}

GLvoid cbMouseMotion(int x, int y)
{
	GM->cbMouseMotion(x, y);
}

GLvoid cbMousePassiveMotion(int x, int y)
{
	GM->cbMousePassiveMotion(x, y);
}

