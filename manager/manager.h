/*
 * $File: manager.h
 * $Date: Thu Dec 02 23:05:26 2010 +0800
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

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <GL/glut.h>

/* ------------ Keyboard consts ----------- */
#define KEY_ESCAPE								27
#define KEY_PAGE_UP								GLUT_KEY_PAGE_UP
#define KEY_PAGE_DOWN							GLUT_KEY_PAGE_DOWN
#define KEY_UP									GLUT_KEY_UP
#define KEY_DOWN								GLUT_KEY_DOWN
#define KEY_LEFT								GLUT_KEY_LEFT
#define KEY_RIGHT								GLUT_KEY_RIGHT
#define KEY_HOME								GLUT_KEY_HOME
#define KEY_END									GLUT_KEY_END
#define KEY_INSERT								GLUT_KEY_INSERT

/* ------------- Mouse consts -------------- */
#define MOUSE_LEFT_BUTTON						GLUT_LEFT_BUTTON
#define MOUSE_MIDDLE_BUTTON						GLUT_MIDDLE_BUTTON
#define MOUSE_RIGHT_BUTTON						GLUT_RIGHT_BUTTON
#define MOUSE_DOWN								GLUT_DOWN
#define MOUSE_UP								GLUT_UP

/* -------------- Game states -------------- */
#define GAME_STATE_NONE							-1
#define GAME_STATE_INIT							0
#define GAME_STATE_MENU							1
#define GAME_STATE_STARTING						2
#define GAME_STATE_RUN							3
#define GAME_STATE_EXIT							4

#define N_GAME_STATE							(GAME_STATE_EXIT + 1)

/* ----------- Game state progress --------- */
#define GAME_STATE_PROGRESS_NONE				-1
#define GAME_STATE_PROGRESS_LOADING				0
#define GAME_STATE_PROGRESS_RUNNING				1
#define GAME_STATE_PROGRESS_EXITING				2


class GameState
{
	public:
		/*
		 * call when game state changed to a specific one
		 * the progress turned to be GAME_STATE_PROGRESS_LOADING
		 * the loading animation should be rendered here
		 * the game manager will hold calling this function until 
		 *		its return value is 1
		 */
		virtual int Init() = 0;

		/*
		 * call when program is idle, the logic parts can be 
		 *		calculated here
		 */
		virtual int Idle() = 0;

		/*
		 * call when time to render, when progress of the gamestate
		 *		is GAME_STATE_PROGRESS_RUNNING
		 */
		virtual int Render() = 0;

		/*
		 * call when about to exit
		 * the progress turned to be GAME_STATE_PROGRESS_EXITING
		 * the exit animation should be rendered here
		 * the game manager will hold calling this function until 
		 *		its return value is 1
		 */
		virtual int Exit() = 0;

		/*
		 * see OpenGL libraries 
		 */
		virtual void cbMouseEvent(int button, int state, int x, int y) = 0;
		virtual void cbMousePassiveMotion(int x, int y) = 0;
		virtual void cbMouseMotion(int x, int y) = 0;
		virtual void cbKeyPressed(unsigned char key, int x, int y) = 0;
		virtual void cbKeyUp(unsigned char key, int x, int y) = 0;
		virtual void cbSpecialKeyPressed(int key, int x, int y) = 0;
		virtual void cbSpecialKeyUp(int key, int x, int y) = 0;
		virtual ~GameState(){};
};


class GameManager;

GameManager* GameManagerInstance();

class GameManager
{
	private:
		/*
		 * construct function
		 */
		GameManager()
		{
			cur_state = GAME_STATE_NONE;
		   	progress = GAME_STATE_PROGRESS_NONE;
		}

		/*
		 * id of current state
		 */
		int cur_state;

		/*
		 * current progress of the state
		 */
		int progress;

		/*
		 * the next state stored while current state is exiting
		 */
		int next_state;

		/*
		 * the list of game states
		 */
		GameState* game_state[N_GAME_STATE];

	public:
		/*
		 * call when about to begin
		 */
		void Init();

		/*
		 * call when idle, this is the main progress
		 */
		void Idle();

		/*
		 * call when rendering is needed
		 */
		void Render();

		/*
		 * call when you want to exit
		 */
		void Exit();

		/*
		 * get the only global instance
		 */
		friend GameManager* GameManagerInstance();

		/*
		 * return the instance of current game state,
		 * if game state is GAME_STATE_NONE, NULl will be returned
		 */
		GameState* CurState();

		/*
		 * change game state to a specific one
		 */
		bool ChangeState(int state);

		/*
		 * register game states
		 */
		bool RegisterGameStateInstance(int state, GameState *game_state_instance);

		/*
		 * call back functions, see OpenGL library
		 */
		void cbKeyPressed(unsigned char key, int x, int y);
		void cbKeyUp(unsigned char key, int x, int y);
		void cbSpecialKeyPressed(int key, int x, int y);
		void cbSpecialKeyUp(int key, int x, int y);
		void cbMouseEvent(int button, int state, int x, int y);
		void cbMouseMotion(int x, int y);
		void cbMousePassiveMotion(int x, int y);
};

#define DECLARE_GAME_STATE_CLASS_DEFAULT_MEMBER_FUNCTION(CLS_NAME) \
	private: \
		GameState##CLS_NAME(); \
	public: \
		static GameState##CLS_NAME* GetInstance() \
		{ \
			static GameState##CLS_NAME game_state; \
			return &game_state; \
		} \
		int Init(); \
		int Idle(); \
		int Render(); \
		int Exit(); \
		void cbMouseEvent(int button, int state, int x, int y); \
		void cbMousePassiveMotion(int x, int y); \
		void cbMouseMotion(int x, int y); \
		void cbKeyPressed(unsigned char key, int x, int y); \
		void cbKeyUp(unsigned char key, int x, int y); \
		void cbSpecialKeyPressed(int key, int x, int y); \
		void cbSpecialKeyUp(int key, int x, int y); \

//#include "game_state_init.h"
//#include "game_state_menu.h"
//#include "game_state_starting"
#include "game_state_run.h"
//#include "game_state_exit"

#endif // __GAME_MANAGER_H__
