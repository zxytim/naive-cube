/*
 * $File: game_phase_run.h
 * $Date: Wed Dec 29 09:15:35 2010 +0800
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
#include <list>
#include "game.h"
#include "cube.h"

class GamePhaseRun : public GamePhase
{
	GAME_PHASE_DEFAULT_DECLARATION
	public:
		GamePhaseRun();
		~GamePhaseRun();

	private:

		/*
		 * Store the global only instance of Renderer
		 */
		Renderer *renderer;

		/*
		 * The cube you are playing
		 */
		Cube *cube;
};

