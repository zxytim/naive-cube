/*
 * $File: game_phase_run.cpp
 * $Date: Tue Dec 28 17:30:28 2010 +0800
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
#include "game_phase_run.h"
#include <cmath>

GamePhaseRun::GamePhaseRun()
{
	renderer = Renderer::instance();
	cube = new Cube();
	addCubeView(true, 1.0f, 0, 0, 0, 0);
}

GamePhaseRun::~GamePhaseRun()
{
	delete cube;
	for (std::list<CubeView *>::iterator it = cube_views.begin(); 
			it != cube_views.end(); it ++)
		delete *it;
}

std::string GamePhaseRun::name()
{
	return "GamePhaseRun";
}


void GamePhaseRun::addCubeView(bool visible, GLfloat cube_size, GLfloat relative_x, GLfloat relative_y, GLfloat turn, GLfloat tilt)
{
	CubeView *cv = new CubeView();
	cv->visible = visible;
	cv->cube_size = cube_size;
	cv->relative_x= relative_x;
	cv->relative_y = relative_y;
	cv->turn = turn;
	cv->tilt = tilt;
	cube_views.push_back(cv);
}

int GamePhaseRun::loading()
{
	return true;
}

int GamePhaseRun::render()
{
	renderer->beginRender();

	for (std::list<CubeView *>::iterator cube_view = cube_views.begin();
			cube_view != cube_views.end(); cube_view ++)
	{
		CubeView *cv = (*cube_view);


		GLfloat ratio = (GLfloat)renderer->width() / renderer->height();

		GLfloat sight_height = -CUBE_CENTER_Z * 2.0 * tan(VIEW_ANGLE / 180.0 * M_PI / 2);
		GLfloat sight_width = ratio * sight_height;

		cv->position.x = sight_width * cv->relative_x;
		cv->position.y = sight_height * cv->relative_y;
		cv->position.z = CUBE_CENTER_Z;

		renderer->pushMatrix();


		renderer->setColor(1, 1, 1);
		renderer->moveView(cv->position.x, cv->position.y, cv->position.z);


		renderer->rotateView(cv->turn, 0, 1, 0);
		renderer->rotateView(cv->tilt, 1, 0, -1);

		cube->drawCube(renderer, cv);

		renderer->popMatrix();
	}

	renderer->endRender();
}


int GamePhaseRun::exiting()
{
	return true;
}


