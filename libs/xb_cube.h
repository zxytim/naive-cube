/*
 * $File: xb_cube.h
 * $Date: Thu Dec 02 18:26:32 2010 +0800
 * $Author: Ted Yin <ymf111111@163.com>
 *
 * @package:Xube Alpha 1
 * @license:GNU Lesser General Public License 3 or any later version                   
 * @note:CST in $Date means China Standard Time instead of Central Standard Time
 */

#ifndef XB_CUBE_H
#define XB_CUBE_H

typedef unsigned int Uint;

/*
   Color Settings

 * 1 -- Blue
 * 2 -- Orange
 * 3 -- Yellow
 * 4 -- Green
 * 5 -- Red
 * 6 -- White

 Planes Settings

 * 1 -- Up
 * 2 -- Down
 * 3 -- Front
 * 4 -- Left
 * 5 -- Back
 * 6 -- Right 

*/

void Xube_init();//initialize

typedef int Xube_plane[7][4][4];

class Xube_State {

	private:
		Uint posc,dirc; //corners
		Uint e1,e2,e3; //edges
	public:

		//int planes[7][4][4], tplanes[7][4][4]; // visiable planes for users

		void bit_view(Uint x,int y);
		void cube_view(Xube_plane tplanes);
		void cube_load(Xube_plane planes); 

		/////         ROTATIONS          //////

		//////////////////////////   UP   //////////////////////////////

		void rotate_up ();
		void rotate_up_ ();

		//////////////////////////   Down   //////////////////////////

		void rotate_down ();
		void rotate_down_ ();

		//////////////////////////   Left   ///////////////////////////

		void rotate_left();
		void rotate_left_();

		///////////////////////////   Right   //////////////////////////

		void rotate_right();
		void rotate_right_();

		////////////////////////   Font   ////////////////////////////

		void rotate_front();
		void rotate_front_();

		//////////////////////////   Back   //////////////////////////

		void rotate_back();
		void rotate_back_(); 

		////////////////////////////////////////////////////////
};

#endif // XB_CUBE_H
