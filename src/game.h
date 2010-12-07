/*
 * $File: game.h
 * $Date: Tue Dec 07 17:34:44 2010 +0800
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

#ifndef HEADER_GAME
#define HEADER_GAME

#include "header.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "renderer.h"
#include "input.h"

#define GAME_DEFAULT_FPS			60

enum GamePhaseType
{
	GAME_PHASE_NONE,
	GAME_PHASE_INIT,
	GAME_PHASE_MENU,
	GAME_PHASE_RUN,
	GAME_PHASE_EXIT,
	N_GAME_PHASE
};

enum GamePhaseProgress
{
	GAME_PHASE_PROGRESS_LOADING,
	GAME_PHASE_PROGRESS_RUNNING,
	GAME_PHASE_PROGRESS_EXITING
};

class Renderer;
class Input;
class GamePhase;

class Game
{
	friend class Input;
	private:
		static GLvoid glcbDisplay();
		static GLvoid glcbIdle();
		static GLvoid glcbReshape(int width, int height);

	public:
		static Game* instance();
		void init(int argc, char *argv[]);
		void setFPS(int fps);

		void execute();

	private:
		Game();
		~Game();

		GamePhaseType cur_phase;
		GamePhaseType next_phase;

		GamePhase *curPhase();

		GamePhaseProgress phase_progress;

		Renderer *renderer;
		Input *input;
		GamePhase *game_phase[N_GAME_PHASE];


		int fps;
		void exit();

		void registerGamePhase(GamePhase *phase, GamePhaseType phase_id);
		void switchPhase(GamePhaseType phase_id);

		void render();
		void idle();
		void reshape(int width, int height);

		void keyPressed(int key);
		void keyReleased(int key);

		void mouseUp(int button, int x, int y);
		void mouseDown(int button, int x, int y);
		void mouseMove(int x, int y);
};

class GamePhase
{
	public:
		GamePhase();
		~GamePhase();
		/*
		 * Game manager will hold on calling the functions below until they
		 * return true
		 */
		/*
		 * Call when this phase is about to begin
		 */
		virtual int loading() = 0;

		/*
		 * Call when time to render a frame
		 * Logical calculations included
		 */
		virtual int render() = 0;

		/*
		 * Call when this phase is about to exit
		 */
		virtual int exiting() = 0;

		/*
		 * Call when key pressed or released
		 */
		void keyPressed(int key);
		void keyReleased(int key);

		/*
		 * Call when mouse has some action
		 */
		void mouseUp(int key, int x, int y);
		void mouseDown(int key, int x, int y);
		void mouseMove(int x, int y);
};

#define GAME_PHASE_DEFAULT_DECLARATION \
	friend class Game; \
	private: \
		int loading(); \
		int render(); \
		int exiting(); \
		void keyPressed(int key); \
		void keyReleased(int key); \
		void mouseUp(int key, int x, int y); \
		void mouseDown(int key, int x, int y); \
		void mouseMove(int x, int y); \

#endif // HEADER_GAME
