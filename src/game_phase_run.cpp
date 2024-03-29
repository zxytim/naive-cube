/*
 * $File: game_phase_run.cpp
 * $Date: Fri Dec 31 13:13:13 2010 +0800
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
	cube = new Cube(3, 3, 3);
}

GamePhaseRun::~GamePhaseRun()
{
	delete cube;
}

std::string GamePhaseRun::name()
{
	return "GamePhaseRun";
}


int GamePhaseRun::loading()
{
	return true;
}

int GamePhaseRun::render()
{
//	renderer->beginRender();
	renderer->pushMatrix();

	renderer->moveView(0, 0, CUBE_CENTER_Z);

	static GLfloat turn = 0, tilt = 0;
	renderer->rotateView(turn, 0, 1, 0);
	renderer->rotateView(tilt, 1, 0, -1);
	turn += 0.2;
	tilt += 0.3;

	/*
	const int N_QUADS = 10;
	const Point p[4] = {Point(0, 0, 0), Point(1, 0, 0), Point(1, 1, 0), Point(0, 1, 0)};
	GLfloat step = 1.0 / N_QUADS;
	GLfloat size = 1.0 / N_QUADS * 3;
	glScalef(size, size, size);
	GLfloat t = 0;
	for (int i = 0; i < N_QUADS; i ++)
	{
		glPushMatrix();
		//glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(0, 0, t += step);
		glTranslatef(i - N_QUADS * 0.5, 0, 0);
		renderer->drawQuad(p);
		//glPopAttrib();
		glPopMatrix();
	}
	*/

	cube->drawCube(renderer);

	renderer->popMatrix();
	//renderer->endRender();
}

int GamePhaseRun::exiting()
{
	return true;
}

void GamePhaseRun::keyPressed(int key)
{
}

void GamePhaseRun::keyReleased(int key)
{
}

