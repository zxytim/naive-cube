
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

/* -------------- Game states -------------- */
#define GAME_STATE_INIT							0
#define GAME_STATE_MENU							1
#define GAME_STATE_STARTING						2
#define GAME_STATE_RUN							3
#define GAME_STATE_EXIT							4

#define N_GAME_STATE							(GAME_STATE_EXIT + 1)

class GameState
{
	public:
		/*
		 * call when game state changed to a specific one
		 */
		virtual void Init() = 0;

		/*
		 * call when program is idle
		 */
		virtual void Idle() = 0;

		/*
		 * call when time to render
		 */
		virtual void Render() = 0;

		/*
		 * call when about to exit
		 */
		virtual void Exit() = 0;

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
};


class GameManager;

GameManager* GameManagerInstance();

class GameManager
{
	private:
		GameManager(){cur_state = GAME_STATE_INIT;}
		int cur_state;
		GameState* game_state[N_GAME_STATE];
	public:
		void Init();
		void Idle();
		void Render();
		void Exit();
		friend GameManager* GameManagerInstance();
		GameState* CurState();
		bool ChangeState(int state);
		bool RegisterGameStateInstance(int state, GameState &game_state_instance);

		void cbKeyPressed(unsigned char key, int x, int y);
		void cbKeyUp(unsigned char key, int x, int y);
		void cbSpecialKeyPressed(int key, int x, int y);
		void cbSpecialKeyUp(int key, int x, int y);
		void cbMouseEvent(int button, int state, int x, int y);
		void cbMouseMotion(int x, int y);
		void cbMousePassiveMotion(int x, int y);
};

#define DECLARE_GAME_STATE_CLASS(class_name) \
	class GameState##class_name : public GameState \
{ \
	void Init(); \
	void Idle(); \
	void Render(); \
	void Exit(); \
	void cbMouseEvent(int button, int state, int x, int y); \
	void cbMousePassiveMotion(int x, int y); \
	void cbMouseMotion(int x, int y); \
	void cbKeyPressed(unsigned char key, int x, int y); \
	void cbKeyUp(unsigned char key, int x, int y); \
	void cbSpecialKeyPressed(int key, int x, int y); \
	void cbSpecialKeyUp(int key, int x, int y); \
};

#include "game_state_init.h"
#include "game_state_menu.h"
//#include "game_state_starting"
#include "game_state_run.h"
//#include "game_state_exit"

#endif // __GAME_MANAGER_H__
