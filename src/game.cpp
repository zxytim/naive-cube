/*
 * $File: game.cpp
 * $Date: Mon Dec 20 21:00:39 2010 +0800
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

GamePhase *Game::nextPhase()
{
	return game_phase[next_phase];
}

void Game::registerGamePhase(GamePhase *phase, GamePhaseType phase_id)
{
	game_phase[phase_id] = phase;
	Log::log(LOG_LEVEL_INFO, __("GamePhase `%s' registered", phase->name().c_str()));
}

void Game::switchPhase(GamePhaseType phase)
{
	Log::log(LOG_LEVEL_INFO, __("Switch to phase `%s'", game_phase[phase]->name().c_str()));
	if (curPhase())
	{
		Log::log(LOG_LEVEL_INFO, __("Phase `%s' exiting ...", curPhase()->name().c_str()));
		phase_progress = GAME_PHASE_PROGRESS_EXITING;
		next_phase = phase;
	}
	else
	{
		cur_phase = phase;
		Log::log(LOG_LEVEL_INFO, __("Phase `%s' start loading ...", curPhase()->name().c_str()));
		phase_progress = GAME_PHASE_PROGRESS_LOADING;
	}
}

void Game::init(int argc, char *argv[])
{
	Log::log(LOG_LEVEL_INFO, "Initializing...");
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

	/*
	 * Log settings
	 */
	Log::disable(LOG_LEVEL_CRITICAL);
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
				Log::log(LOG_LEVEL_INFO, __("Phase `%s' loading finished", curPhase()->name().c_str()));
				phase_progress = GAME_PHASE_PROGRESS_RUNNING;
			}
			break;

		case GAME_PHASE_PROGRESS_RUNNING:
			curPhase()->render();
			break;

		case GAME_PHASE_PROGRESS_EXITING:
			if (curPhase()->exiting())
			{
				Log::log(LOG_LEVEL_INFO, __("Phase `%s' exited", curPhase()->name().c_str()));
				Log::log(LOG_LEVEL_INFO, __("Phase `%s' start loading ...", nextPhase()->name().c_str()));
				phase_progress = GAME_PHASE_PROGRESS_LOADING;
				cur_phase = next_phase;
				next_phase = GAME_PHASE_NONE;
			}
	}
	timer.begin();
}

void Game::reshape(int width, int height)
{
	Log::log(LOG_LEVEL_INFO, __("Window size changing to %dx%d", width, height));
	renderer->reshape(width, height);
}

void Game::setFPS(int fps_)
{
	Log::log(LOG_LEVEL_INFO, __("FPS is set to %d", fps_));
	fps = fps_;
}

void Game::exit()
{
	Log::log(LOG_LEVEL_INFO, "Game exiting...");
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
	Log::log(LOG_LEVEL_CRITICAL, __("Key <%s> pressed", Input::getKeyName(key).c_str()));
	curPhase()->keyPressed(key);
}

void Game::keyReleased(int key)
{
	Log::log(LOG_LEVEL_CRITICAL, __("Key <%s> released", Input::getKeyName(key).c_str()));
	curPhase()->keyReleased(key);
}


void Game::mouseUp(int button, int x, int y)
{
	Log::log(LOG_LEVEL_CRITICAL, __("Mouse button <%s> up", Input::getMouseButtonName(button).c_str()));
	curPhase()->mouseUp(button, x, y);
}

void Game::mouseDown(int button, int x, int y)
{
	Log::log(LOG_LEVEL_CRITICAL, __("Mouse button <%s> down", Input::getMouseButtonName(button).c_str()));
	curPhase()->mouseDown(button, x, y);
}

void Game::mouseMove(int x, int y)
{
	Log::log(LOG_LEVEL_CRITICAL, __("Mouse move to (%d, %d)", x, y));
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

