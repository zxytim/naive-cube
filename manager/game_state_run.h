
#ifndef __GAME_STATE_RUN_H__
#define __GAME_STATE_RUN_H__

#include "manager.h"
#include "../cube.h"

class GameStateRun : public GameState
{
	private:
		void DrawCube(GLfloat len = 1, const Point &center = Point(0, 0, 0), const Color *colors = NULL);
		DECLARE_GAME_STATE_CLASS_DEFAULT_MEMBER_FUNCTION(Run);
		Point eye_pos;
		Point cube_center;
		Point normal_dir;
		bool keys[256];
		bool spkeys[256];
		int mouse_x, mouse_y;
};
#endif // __GAME_STATE_MENU_H__
