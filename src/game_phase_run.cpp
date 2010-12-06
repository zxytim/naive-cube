/*
 * $File: game_phase_run.cpp
 * $Date: Mon Dec 06 20:17:34 2010 +0800
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

#include "game_phase_run.h"

GamePhaseRun::GamePhaseRun()
{
}

GamePhaseRun::~GamePhaseRun()
{
}

int GamePhaseRun::loading()
{
	return false;
}

int GamePhaseRun::render()
{
}

int GamePhaseRun::exiting()
{
	return true;
}

