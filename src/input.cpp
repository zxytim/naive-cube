/*
 * $File: input.cpp
 * $Date: Mon Dec 06 21:21:11 2010 +0800
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

#include "header.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "input.h"

static int glutspkeys[256];
static int glutmouse[3];
static int mouse_x, mouse_y;

#ifdef DEBUG
#include <string>
static std::string key_name[N_KEYS];
#endif

Input::Input()
{
	/*
	 * Bind mouse button
	 */
#define BIND(mouse, glutm) glutmouse[glutm] = mouse
	BIND(MOUSE_LEFT_BUTTON, GLUT_LEFT_BUTTON);
	BIND(MOUSE_MIDDLE_BUTTON, GLUT_MIDDLE_BUTTON);
	BIND(MOUSE_RIGHT_BUTTON, GLUT_RIGHT_BUTTON);
#undef BIND

	/*
	 * Bind special keys
	 */
#define BIND(key, glutkey) glutspkeys[glutkey] = key
	BIND(KEY_F1, GLUT_KEY_F1);
	BIND(KEY_F2, GLUT_KEY_F2);
	BIND(KEY_F3, GLUT_KEY_F3);
	BIND(KEY_F4, GLUT_KEY_F4);
	BIND(KEY_F5, GLUT_KEY_F5);
	BIND(KEY_F6, GLUT_KEY_F6);
	BIND(KEY_F7, GLUT_KEY_F7);
	BIND(KEY_F8, GLUT_KEY_F8);
	BIND(KEY_F9, GLUT_KEY_F9);
	BIND(KEY_F10, GLUT_KEY_F10);
	BIND(KEY_F11, GLUT_KEY_F11);
	BIND(KEY_F12, GLUT_KEY_F12);
	BIND(KEY_LEFT, GLUT_KEY_LEFT);
	BIND(KEY_UP, GLUT_KEY_UP);
	BIND(KEY_RIGHT, GLUT_KEY_RIGHT);
	BIND(KEY_DOWN, GLUT_KEY_DOWN);
	BIND(KEY_PAGE_UP, GLUT_KEY_PAGE_UP);
	BIND(KEY_PAGE_DOWN, GLUT_KEY_PAGE_DOWN);
	BIND(KEY_HOME, GLUT_KEY_HOME);
	BIND(KEY_END, GLUT_KEY_END);
	BIND(KEY_INSERT, GLUT_KEY_INSERT);
#undef BIND

#ifdef DEBUG
	key_name[KEY_ESCAPE]		= "Esc";
	key_name[KEY_F1]			= "F1";
	key_name[KEY_F2]			= "F2";
	key_name[KEY_F3]			= "F3";
	key_name[KEY_F4]			= "F4";
	key_name[KEY_F5]			= "F5";
	key_name[KEY_F6]			= "F6";
	key_name[KEY_F7]			= "F7";
	key_name[KEY_F8]			= "F8";
	key_name[KEY_F9]			= "F9";
	key_name[KEY_F10]			= "F10";
	key_name[KEY_F11]			= "F11";
	key_name[KEY_F12]			= "F12";
	key_name[KEY_LEFT]			= "Left Arrow";
	key_name[KEY_UP]			= "Up Arrow";
	key_name[KEY_RIGHT]			= "Right Arrow";
	key_name[KEY_DOWN]			= "Down Arrow";
	key_name[KEY_PAGE_UP]		= "Page Up";
	key_name[KEY_PAGE_DOWN]		= "Page Down";
	key_name[KEY_HOME]			= "Home";
	key_name[KEY_END]			= "End";
	key_name[KEY_INSERT]		= "Insert";
	
	for (int i = 0; i < 255; i ++)
		if (isprint(i))
			key_name[i] += (char)i;
		else
			key_name[i] = "code:" + itos(i);
#endif
}

Input::~Input()
{
}

Game * Input::game;

Input * Input::instance()
{
	static Input input;
	return &input;
}

void Input::init(Game *game_)
{
	game = game_;

	/*
	 * Key settings and callbacks
	 */
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glutKeyboardFunc(glcbKeyPressed);

	glutKeyboardUpFunc(glcbKeyReleased);

	glutSpecialFunc(glcbSpecialKeyPressed);

	glutSpecialUpFunc(glcbSpecialKeyReleased);

	glutMouseFunc(glcbMouseEvent);

	glutMotionFunc(glcbMouseMotion);

	glutPassiveMotionFunc(glcbMousePassiveMotion);
}


/*
 * 
 */
void Input::getMousePos(int &x, int &y)
{
	x = mouse_x, y = mouse_y;
}

/*
 * Keyboard callbacks
 */
GLvoid Input::glcbKeyPressed(unsigned char key, int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->keyPressed(key);
}

GLvoid Input::glcbKeyReleased(unsigned char key, int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->keyReleased(key);
}

GLvoid Input::glcbSpecialKeyPressed(int key, int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->keyPressed(glutspkeys[key]);
}

GLvoid Input::glcbSpecialKeyReleased(int key, int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->keyReleased(glutspkeys[key]);
}


/*
 * Mouse callbacks
 */
GLvoid Input::glcbMouseEvent(int button, int state, int x, int y)
{
	mouse_x = x, mouse_y = y;
	if (state == GLUT_DOWN)
		game->mouseDown(glutmouse[button], x, y);
	else
		game->mouseUp(glutmouse[button], x, y);
}

GLvoid Input::glcbMouseMotion(int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->mouseMove(x, y);
}

GLvoid Input::glcbMousePassiveMotion(int x, int y)
{
	mouse_x = x, mouse_y = y;
	game->mouseMove(x, y);
}

#ifdef DEBUG
std::string Input::getKeyName(int key)
{
	return key_name[key];
}
#endif
