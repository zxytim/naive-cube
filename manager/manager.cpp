/*
 * $File: manager.cpp
 * $Date: Wed Dec 01 11:24:57 2010 +0800
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
#include "manager.h"

GameManager* GameManagerInstance()
{
	static GameManager game_manager;
	return &game_manager;
}

GameState* GameManager::CurState()
{
	if (cur_state >= 0 && cur_state < N_GAME_STATE)
		return game_state[cur_state];
	return NULL;
}

void GameManager::Init()
{
}

void GameManager::Idle()
{
	Render();
}

void GameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (progress)
	{
		case GAME_STATE_PROGRESS_LOADING:
			if (CurState()->Init())
				progress = GAME_STATE_PROGRESS_RUNNING;
			break;
		case GAME_STATE_PROGRESS_RUNNING:
			CurState()->Render();
			break;
		case GAME_STATE_PROGRESS_EXITING:
			if (CurState()->Exit())
			{
				progress = GAME_STATE_PROGRESS_LOADING;
				cur_state = next_state;
			}
			break;
	}
	glutSwapBuffers();
}

void GameManager::Exit()
{
}

bool GameManager::ChangeState(int state)
{
	if (state < 0 || state >= N_GAME_STATE)
		return false;

	if (CurState())
	{
		progress = GAME_STATE_PROGRESS_EXITING;
		next_state = state;
	}
	else
	{
		progress = GAME_STATE_PROGRESS_LOADING;
		cur_state = state;
	}
	return true;
}

bool GameManager::RegisterGameStateInstance(int state, GameState *game_state_instance)
{
	if (state < 0 || state >= N_GAME_STATE)
		return false;
	game_state[state] = game_state_instance;
	return true;
}

void GameManager::cbKeyPressed(unsigned char key, int x, int y)
{
	CurState()->cbKeyPressed(key, x, y);
}

void GameManager::cbKeyUp(unsigned char key, int x, int y)
{
	CurState()->cbKeyUp(key, x, y);
}

void GameManager::cbSpecialKeyPressed(int key, int x, int y)
{
	CurState()->cbSpecialKeyPressed(key, x, y);
}

void GameManager::cbSpecialKeyUp(int key, int x, int y)
{
	CurState()->cbSpecialKeyUp(key, x, y);
}

void GameManager::cbMouseEvent(int button, int state, int x, int y)
{
	CurState()->cbMouseEvent(button, state, x, y);
}

void GameManager::cbMouseMotion(int x, int y)
{
	CurState()->cbMouseMotion(x, y);
}

void GameManager::cbMousePassiveMotion(int x, int y)
{
	CurState()->cbMousePassiveMotion(x, y);
}

