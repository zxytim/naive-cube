#include "manager.h"

GameManager* GameManagerInstance()
{
	static GameManager game_manager;
	return &game_manager;
}

GameState* GameManager::CurState()
{
	return game_state[cur_state];
}

void GameManager::Init()
{
}

void GameManager::Idle()
{
}

void GameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	CurState()->Render();
	
	glutSwapBuffers();
}

bool GameManager::ChangeState(int state)
{
	if (state < 0 || state >= N_GAME_STATE)
		return false;
	CurState()->Exit();

	cur_state = state;

	CurState()->Init();

	return true;
}

bool GameManager::RegisterGameStateInstance(int state, GameState &game_state_instance)
{
	if (state < 0 || state >= N_GAME_STATE)
		return false;
	game_state[state] = &game_state_instance;
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


