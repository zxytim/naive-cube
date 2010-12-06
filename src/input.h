/*
 * $File: input.h
 * $Date: Mon Dec 06 21:21:41 2010 +0800
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

#ifndef HEADER_INPUT
#define HEADER_INPUT

#include "header.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "game.h"

/*
 * Special key definations
 */

#define KEY_ESCAPE						0x1B
#define SPKEY_START_POS					0x100
#define KEY_F1							(SPKEY_START_POS + 0x01)
#define KEY_F2							(SPKEY_START_POS + 0x02)
#define KEY_F3							(SPKEY_START_POS + 0x03)
#define KEY_F4							(SPKEY_START_POS + 0x04)
#define KEY_F5							(SPKEY_START_POS + 0x05)
#define KEY_F6							(SPKEY_START_POS + 0x06)
#define KEY_F7							(SPKEY_START_POS + 0x07)
#define KEY_F8							(SPKEY_START_POS + 0x08)
#define KEY_F9							(SPKEY_START_POS + 0x09)
#define KEY_F10							(SPKEY_START_POS + 0x0A)
#define KEY_F11							(SPKEY_START_POS + 0x0B)
#define KEY_F12							(SPKEY_START_POS + 0x0C)
#define KEY_LEFT						(SPKEY_START_POS + 0x0D)
#define KEY_UP							(SPKEY_START_POS + 0x0E)
#define KEY_RIGHT						(SPKEY_START_POS + 0x0F)
#define KEY_DOWN						(SPKEY_START_POS + 0x10)
#define KEY_PAGE_UP						(SPKEY_START_POS + 0x11)
#define KEY_PAGE_DOWN					(SPKEY_START_POS + 0x12)
#define KEY_HOME						(SPKEY_START_POS + 0x13)
#define KEY_END							(SPKEY_START_POS + 0x14)
#define KEY_INSERT						(SPKEY_START_POS + 0x15)
#define N_KEYS							(KEY_INSERT + 1)

/*
 * Mouse contants definations
 */
#define MOUSE_LEFT_BUTTON				0x00
#define MOUSE_MIDDLE_BUTTON				0x01
#define MOUSE_RIGHT_BUTTON				0x02
#define MOUSE_UP						0x00
#define MOUSE_DOWN						0x01

class Game;

class Input
{
	public:
		static Game *game;
		static Input *instance();
		void init(Game *game);
		
		void getMousePos(int &x, int &y);

#ifdef DEBUG
		/*
		 * Debug functions
		 */
		static std::string getKeyName(int key);
#endif

	private:
		Input();
		~Input();

		/*
		 * Keyboard callbacks
		 */
		static GLvoid glcbKeyPressed(unsigned char key, int x, int y);
		static GLvoid glcbKeyReleased(unsigned char key, int x, int y);
		static GLvoid glcbSpecialKeyPressed(int key, int x, int y);
		static GLvoid glcbSpecialKeyReleased(int key, int x, int y);

		/*
		 * Mouse callbacks
		 */
		static GLvoid glcbMouseEvent(int button, int state, int x, int y);
		static GLvoid glcbMouseMotion(int x, int y);
		static GLvoid glcbMousePassiveMotion(int x, int y);
};

#endif // HEADER_INPUT
