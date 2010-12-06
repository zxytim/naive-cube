/*
 * $File: game.cpp
 * $Date: Mon Dec 06 21:24:36 2010 +0800
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
#include <cstring>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "game.h"
#include "game_phase_run.h"
#include "timer.h"

Game::Game()
{
	cur_phase = GAME_PHASE_NONE;
}

Game::~Game()
{
}

Game *Game::instance()
{
	static Game game;
	return &game;
}

GamePhase *Game::curPhase()
{
	return game_phase[cur_phase];
}

void Game::registerGamePhase(GamePhase *phase, GamePhaseType phase_id)
{
#ifdef DEBUG
	DEBUG_INFO(__("GamePhase %d registering", phase_id));
#endif
	game_phase[phase_id] = phase;
}

void Game::switchPhase(GamePhaseType phase)
{
#ifdef DEBUG
	DEBUG_INFO(__("switch to phase %d", phase));
#endif
	if (curPhase())
	{
		phase_progress = GAME_PHASE_PROGRESS_EXITING;
		next_phase = phase;
	}
	else
	{
		phase_progress = GAME_PHASE_PROGRESS_LOADING;
		cur_phase = phase;
	}
}

void Game::init(int argc, char *argv[])
{
#ifdef DEBUG
	DEBUG_INFO("Initializing...");
#endif
	memset(game_phase, 0, sizeof(game_phase));

	registerGamePhase(new GamePhaseRun(), GAME_PHASE_RUN);
	switchPhase(GAME_PHASE_RUN);

	setFPS(GAME_DEFAULT_FPS);
	/*
	 * Initialize renderer
	 */
	renderer = Renderer::instance();
	renderer->init(argc, argv, GAME_NAME, WINDOW_WIDTH_DEFAULT, WINDOW_HEIGHT_DEFAULT);
	renderer->setBackgroundColor(Colorf(0.5, 0.5, 0.5));

	/*
	 * Initialize Input
	 */
	input = Input::instance();
	input->init(this);

	/*
	 * Initialize OpenGL callbacks
	 */
	glutDisplayFunc(glcbDisplay);

	glutIdleFunc(glcbIdle);

	glutReshapeFunc(glcbReshape);
}

void Game::execute()
{
	glutMainLoop();
	exit();
}

void Game::render()
{
	renderer->beginRender();

	renderer->endRender();
}

void Game::idle()
{
	static Timer timer;
	if (timer.end() * fps < 1000)
	{
		timer.sleep(1000 / fps / 2);
		return;
	}

	switch (phase_progress)
	{
		case GAME_PHASE_PROGRESS_LOADING:
			if (curPhase()->loading())
			{
#ifdef DEBUG
				DEBUG_INFO(__("Phase %d loading finished", cur_phase));
#endif
				phase_progress = GAME_PHASE_PROGRESS_RUNNING;
			}
			break;

		case GAME_PHASE_PROGRESS_RUNNING:
			curPhase()->render();
			break;

		case GAME_PHASE_PROGRESS_EXITING:
			if (curPhase()->exiting())
			{
#ifdef DEBUG
				DEBUG_INFO(__("Phase %d exited", cur_phase));
				DEBUG_INFO(__("Phase %d start loading", next_phase));
#endif
				phase_progress = GAME_PHASE_PROGRESS_LOADING;
				cur_phase = next_phase;
			}
	}
	timer.begin();
}

void Game::reshape(int width, int height)
{
#ifdef DEBUG
	DEBUG_INFO(__("Window size changing to %dx%d", width, height));
#endif
	renderer->reshape(width, height);
}

void Game::setFPS(int fps_)
{
#ifdef DEBUG
	DEBUG_INFO(__("FPS is set to %d", fps_));
#endif
	fps = fps_;
}

void Game::exit()
{
#ifdef DEBUG
	DEBUG_INFO("Game exiting...");
#endif
	for (int i = 0; i < N_GAME_PHASE; i ++)
		if (game_phase[i])
			delete game_phase[i];
}

GLvoid Game::glcbDisplay()
{
	Game::instance()->render();
}

GLvoid Game::glcbIdle()
{
	Game::instance()->idle();
}

GLvoid Game::glcbReshape(int width, int height)
{
	Game::instance()->reshape(width, height);
}

void Game::keyPressed(int key)
{
#ifdef DEBUG
	DEBUG_INFO(__("Key <%s> pressed", Input::getKeyName(key).c_str()));
#endif
	curPhase()->keyPressed(key);
}

void Game::keyReleased(int key)
{
	curPhase()->keyReleased(key);
}


void Game::mouseUp(int button, int x, int y)
{
	curPhase()->mouseUp(button, x, y);
}

void Game::mouseDown(int button, int x, int y)
{
	curPhase()->mouseDown(button, x, y);
}

void Game::mouseMove(int x, int y)
{
	curPhase()->mouseMove(x, y);
}


GamePhase::GamePhase()
{
}

GamePhase::~GamePhase()
{
}

void GamePhase::keyPressed(int key)
{
}

void GamePhase::keyReleased(int key)
{
}

void GamePhase::mouseUp(int key, int x, int y)
{
}

void GamePhase::mouseDown(int key, int x, int y)
{
}

void GamePhase::mouseMove(int x, int y)
{
}

