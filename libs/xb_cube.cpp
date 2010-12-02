/*
 * $File: xb_cube.cpp
 * $Date: Thu Dec 02 18:32:45 2010 +0800
 * $Author: Ted Yin <ymf111111@163.com>
 *
 * @package:Xube Alpha 1
 * @license:GNU Lesser General Public License 3 or any later version                   
 * @note:CST in $Date means China Standard Time instead of Central Standard Time
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include "xb_cube.h"

typedef unsigned int Uint;

#define bit10 0xAAAA
#define bit01 0x5555

#define rotate_dir(mask,dirc) { \
	int tmp = (dirc & (mask & bit10)) | ((dirc & (mask & bit10)) >> 1); \
	dirc = (dirc + (bit01 & mask)) ^ tmp; \
}
//Rotate Dir

#define Pclean_bits(x) (pos & (~(0x7 << x)))
#define Dclean_bits(x) (dir & (~(0x3 << x)))
#define Pget_bits(x) (pos & (0x7 << x))
#define Dget_bits(x) (dir & (0x3 << x))

#define Eget_bits(ex,i) (ex & (0x7 << i))
#define Eclean_bits(ex,i) (ex & (~(0x7 << i)))

using namespace std;

char names[7][10] = {"","Up","Down","Front","Left","Right","Back"};
int get_corner[9][3][3] = 
{
	{{0,0,0},{0,0,0},{0,0,0}}, //no use

	{{1,1,1},{5,1,3},{4,1,1}}, //Cor 1
	{{1,1,3},{6,1,3},{5,1,1}}, //Cor 2
	{{1,3,3},{3,1,3},{6,1,1}}, //Cor 3
	{{1,3,1},{4,1,3},{3,1,1}}, //Cor 4

	{{2,1,3},{4,3,1},{5,3,3}}, //Cor 5
	{{2,1,1},{5,3,1},{6,3,3}}, //Cor 6
	{{2,3,1},{6,3,1},{3,3,3}}, //Cor 7
	{{2,3,3},{3,3,1},{4,3,3}} // Cor 8
};//Oh ...My God!!!

//eight corner postions
/*
		1------2
       /      /|
      /      / |
     4------3  |
     |      |  |
     |      |  |
     |      | /6	 
     8------7/

*/

/*

 * get_corner[x][0]; Up/Down face
 * get_corner[x][1]; The other side Left
 * get_corner[x][2]; The other side Right
 * get_corner[x][y] = {plane,i,j};

*/

int get_num[7][7][7]; // get_number[c1][c2][c3];
int get_dir[9][7]; //get_dir[Corner_NUM][Up/Down face];

int view[7][5] = {
	{0,0,0,0,0}, //no use
	{0,1,2,4,3}, //Up
	{0,8,7,5,6}, //Down
	{0,4,3,8,7}, //Front
	{0,1,4,5,8}, //Left
	{0,2,1,6,5}, //Back
	{0,3,2,7,6} //Right
};

/*
   View -- View 6 sides (except Up&Down)
   each side is like this

   [1]-------[2]
    |         |
    |         |
    |         |
   [3]-------[4]
*/

int get_col[9][3][3];//get_col[Corner_NUM][Up/down Num] = {LeftCol,RightCol,UpCol}
int cen[7] = {0,3,6,1,2,4,5};// the color of center 

int e1_view[8][3] = {{3,1,2},{3,2,3},{3,3,2},{3,2,1}, //front
	{5,3,2},{5,2,1},{5,1,2},{5,2,3} //back
}; //convert e1's edges to plane positions

int e2_view[8][3] = {{1,1,2},{1,2,3},{1,3,2},{1,2,1}, //up
	{2,1,2},{2,2,3},{2,3,2},{2,2,1} //down
}; //convert e2's edges to plane positions

int e3_view[8][3] = {{4,1,2},{4,2,3},{4,3,2},{4,2,1}, //left
	{6,1,2},{6,2,3},{6,3,2},{6,2,1} //right
}; //convert e3's edges to plane positions


/*      About Edges
 *
 *	       . 1 .
 *	       4 B 2
 *	       . 3 .
 *
 *  . 1 .  . 1 .  . 5 .
 *  4 C 2  4 A 2  8 C 6
 *  . 3 .  . 3 .  . 7 .
 *
 *         . 5 .
 *         8 B 6
 *         . 7 .
 *
 *         . 5 .
 *         8 A 6
 *         . 7 .
 *
 *    A =  = E1 B =  = E2 C =  = E3
*/

void Xube_State::cube_view(Xube_plane tplanes) {

	//Up & Down
	memset(tplanes,0,sizeof(Xube_plane));
	for (int i = 1; i<= 6; i++)
	{
		int x1 = view[i][1],x2 = view[i][2],x3 = view[i][3],x4 = view[i][4];//get postions

		int n1 = (posc & (0x7 << ((x1 - 1) * 3))) >> ((x1 - 1) * 3),
			n2 = (posc & (0x7 << ((x2 - 1) * 3))) >> ((x2 - 1) * 3),
			n3 = (posc & (0x7 << ((x3 - 1) * 3))) >> ((x3 - 1) * 3),
			n4 = (posc & (0x7 << ((x4 - 1) * 3))) >> ((x4 - 1) * 3);

		int d1 = (dirc & (0x3 << ((x1 - 1) << 1))) >> ((x1 - 1) << 1),
			d2 = (dirc & (0x3 << ((x2 - 1) << 1))) >> ((x2 - 1) << 1),
			d3 = (dirc & (0x3 << ((x3 - 1) << 1))) >> ((x3 - 1) << 1),
			d4 = (dirc & (0x3 << ((x4 - 1) << 1))) >> ((x4 - 1) << 1);

		int o1,o2,o3,o4;

		if (i<= 2) o1 = 2,o2 = 2,o3 = 2,o4 = 2; else o1 = 1,o2 = 0,o3 = 0,o4 = 1;
		int c1 = get_col[n1+1][d1][o1],
			c2 = get_col[n2+1][d2][o2],
			c3 = get_col[n3+1][d3][o3],
			c4 = get_col[n4+1][d4][o4];

		tplanes[i][1][1] = c1; tplanes[i][1][3] = c2;
		tplanes[i][2][2] = cen[i];
		tplanes[i][3][1] = c3; tplanes[i][3][3] = c4;

	}
	//Corners' view completed!

	for (int i = 0; i<8; i++)
	{
		Uint v = Eget_bits(e1,(i * 3)) >> (i * 3);
		tplanes[e1_view[i][0]][e1_view[i][1]][e1_view[i][2]] = v;
	}//Load E1

	for (int i = 0; i<8; i++)
	{
		Uint v = Eget_bits(e2,(i * 3)) >> (i * 3);
		tplanes[e2_view[i][0]][e2_view[i][1]][e2_view[i][2]] = v;
	}//Load E2

	for (int i = 0; i<8; i++)
	{
		Uint v = Eget_bits(e3,(i * 3)) >> (i * 3);
		tplanes[e3_view[i][0]][e3_view[i][1]][e3_view[i][2]] = v;
	}//Load E3

	for (int i = 1; i<= 3; i++)
	{
		for (int k = 1; k<= 6; k++)
		{
			for (int j = 1; j<= 3; j++)
				printf("%d ",tplanes[k][i][j]);
			printf(" ");
		}
		printf("\n");
	}
	for (int i = 1; i<= 6; i++) printf("  %s ",names[i]); printf("\n");
	//print all planes

	printf("-----------------------------------------\n");
}


void Xube_State::bit_view(Uint x,int y) {

	int li[33],limit = y*8;
	memset(li,0,sizeof(li));
	while (x) {li[++li[0]] = x%2;x >>= 1;}
	for (int i = limit; i >= 1; i--) {if (!(i%y))printf(" ");printf("%d",li[i]);}	
}
/* {{{ void cube_init */
void Xube_init() {

	memset(get_num,0,sizeof(get_num));

	get_num[3][4][2] = get_num[4][2][3] = get_num[2][3][4] = 1; //CorNum1
	get_num[3][2][1] = get_num[2][1][3] = get_num[1][3][2] = 2; //CorNum2
	get_num[3][5][4] = get_num[5][4][3] = get_num[4][3][5] = 3; //CorNum3
	get_num[3][1][5] = get_num[1][5][3] = get_num[5][3][1] = 4; //CorNum4

	get_num[6][2][4] = get_num[4][6][2] = get_num[2][4][6] = 5; //CorNum5
	get_num[6][1][2] = get_num[2][6][1] = get_num[1][2][6] = 6; //CorNum6
	get_num[6][4][5] = get_num[5][6][4] = get_num[4][5][6] = 7; //CorNum7
	get_num[6][5][1] = get_num[1][6][5] = get_num[5][1][6] = 8; //CorNum8

	memset(get_dir,0,sizeof(get_dir));

	get_dir[1][3] = 1; get_dir[1][4] = 2; get_dir[1][2] = 3;
	get_dir[2][3] = 1; get_dir[2][2] = 2; get_dir[2][1] = 3;
	get_dir[3][3] = 1; get_dir[3][5] = 2; get_dir[3][4] = 3;
	get_dir[4][3] = 1; get_dir[4][1] = 2; get_dir[4][5] = 3;

	get_dir[5][6] = 1; get_dir[5][2] = 2; get_dir[5][4] = 3;
	get_dir[6][6] = 1; get_dir[6][1] = 2; get_dir[6][2] = 3;
	get_dir[7][6] = 1; get_dir[7][4] = 2; get_dir[7][5] = 3;
	get_dir[8][6] = 1; get_dir[8][5] = 2; get_dir[8][1] = 3;

	memset(get_col,0,sizeof(get_col));

	get_col[1][0][0] = 4; get_col[1][0][1] = 2; get_col[1][0][2] = 3;   get_col[1][1][0] = 2; get_col[1][1][1] = 3; get_col[1][1][2] = 4;   get_col[1][2][0] = 3; get_col[1][2][1] = 4; get_col[1][2][2] = 2;

	get_col[2][0][0] = 2; get_col[2][0][1] = 1; get_col[2][0][2] = 3;   get_col[2][1][0] = 1; get_col[2][1][1] = 3; get_col[2][1][2] = 2;   get_col[2][2][0] = 3; get_col[2][2][1] = 2; get_col[2][2][2] = 1;

	get_col[3][0][0] = 5; get_col[3][0][1] = 4; get_col[3][0][2] = 3;   get_col[3][1][0] = 4; get_col[3][1][1] = 3; get_col[3][1][2] = 5;   get_col[3][2][0] = 3; get_col[3][2][1] = 5; get_col[3][2][2] = 4;

	get_col[4][0][0] = 1; get_col[4][0][1] = 5; get_col[4][0][2] = 3;   get_col[4][1][0] = 5; get_col[4][1][1] = 3; get_col[4][1][2] = 1;   get_col[4][2][0] = 3; get_col[4][2][1] = 1; get_col[4][2][2] = 5;

	get_col[5][0][0] = 2; get_col[5][0][1] = 4; get_col[5][0][2] = 6;   get_col[5][1][0] = 4; get_col[5][1][1] = 6; get_col[5][1][2] = 2;   get_col[5][2][0] = 6; get_col[5][2][1] = 2; get_col[5][2][2] = 4;

	get_col[6][0][0] = 1; get_col[6][0][1] = 2; get_col[6][0][2] = 6;   get_col[6][1][0] = 2; get_col[6][1][1] = 6; get_col[6][1][2] = 1;   get_col[6][2][0] = 6; get_col[6][2][1] = 1; get_col[6][2][2] = 2;

	get_col[7][0][0] = 4; get_col[7][0][1] = 5; get_col[7][0][2] = 6;   get_col[7][1][0] = 5; get_col[7][1][1] = 6; get_col[7][1][2] = 4;   get_col[7][2][0] = 6; get_col[7][2][1] = 4; get_col[7][2][2] = 5;

	get_col[8][0][0] = 5; get_col[8][0][1] = 1; get_col[8][0][2] = 6;   get_col[8][1][0] = 1; get_col[8][1][1] = 6; get_col[8][1][2] = 5;   get_col[8][2][0] = 6; get_col[8][2][1] = 5; get_col[8][2][2] = 1;

	//This programmer is fairly lazy...
}
/* }}} */

void Xube_State::cube_load(Xube_plane planes) {

	memset(planes, 0, sizeof(Xube_plane));
	posc = 0;
	dirc = 0;
	for (int i = 1; i<= 8; i++)
	{
		int *splaneD = get_corner[i][0];
		int *splaneL = get_corner[i][1];
		int *splaneR = get_corner[i][2];
		//
		int Dcolor = planes[splaneD[0]][splaneD[1]][splaneD[2]];
		int colorL = planes[splaneL[0]][splaneR[1]][splaneR[2]];
		int colorR = planes[splaneR[0]][splaneL[1]][splaneL[2]];
		//
		int num = get_num[Dcolor][colorL][colorR];//num of this corner
		int dir = get_dir[num][Dcolor];//dir of this corner

		Uint maskD = 0x3 << ( ( i - 1 ) << 1 );
		Uint maskP = 0x7 << ( ( i - 1 ) * 3 );

		posc &= ~maskP; //clear position to 000
		posc |= ( num - 1 ) << ( ( i - 1 ) * 3 );//write position value
		dirc &= ~maskD; //clear dir to 000
		dirc |= ( dir - 1 ) << ( ( i - 1 ) << 1 );//write dir value
		/*
		   printf("Test on Corner:%d -. num:%d  dir:%d ",i,num,dir);
		   printf("POSC is now: "); bit_view(posc,3);
		   printf(" DIRC is now: "); bit_view(dirc,2);
		   printf("\n");
		*/
	}
	//Load Corners 


	for (int i = 0; i<8; i++)
	{
		Uint v = planes[e1_view[i][0]][e1_view[i][1]][e1_view[i][2]];
		e1 = Eclean_bits(e1,i * 3) | (v << (i * 3));
	}//Load E1

	for (int i = 0; i<8; i++)
	{
		Uint v = planes[e2_view[i][0]][e2_view[i][1]][e2_view[i][2]];
		e2 = Eclean_bits(e2,i * 3) | (v << (i * 3));
	}
	//Load E2
	for (int i = 0; i<8; i++)
	{
		Uint v = planes[e3_view[i][0]][e3_view[i][1]][e3_view[i][2]];
		e3 = Eclean_bits(e3,i * 3) | (v << (i * 3));
	}
	//Load E3
}


/////         ROTATIONS          //////


//////////////////////////   UP   //////////////////////////////

void Xube_State::rotate_up () {

	Uint pos = posc,dir = dirc;
	Uint p4 = ((0x7 << 9) & pos) >> 9; //get pos 4
	Uint d4 = ((0x3 << 6) & dir) >> 6; //get dir 4
	Uint tmpp = (0x0001FF & pos) << 3; //get pos 1,2,3
	Uint tmpd = (0x003F & dir) << 2; //get dir 1,2,3
	posc = (pos & (~0x000FFF)) | tmpp | p4;
	dirc = (dir & (~0x00FF)) | tmpd | d4;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te11 = Eget_bits(E1,0); //get 1(1)
	E1 = Eclean_bits(E1,0) | (Eget_bits(E3,12) >> 12); //5(3) to 1(1)  
	E3 = Eclean_bits(E3,12) | (Eget_bits(E1,18) >> 6); //7(1) to 5(3) 
	E1 = Eclean_bits(E1,18) | (Eget_bits(E3,0) << 18); //1(3) to 7(1)
	E3 = Eclean_bits(E3,0) | te11; //1(1) to 1(3)
	Uint te24 = Eget_bits(E2,9);
	E2 = (E2 & 0xFFF000) | ((E2 & 0x0001FF) << 3) | (te24 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}

void Xube_State::rotate_up_ () {

	Uint pos = posc,dir = dirc;
	Uint p1 = (0x7 & pos) << 9; //get pos 1
	Uint d1 = (0x3 & dir) << 6; //get dir 1
	Uint tmpp = (0x000FF8 & pos) >> 3; //get pos 2,3,4
	Uint tmpd = (0x00FC & dir) >> 2; //get dir 2,3,4
	posc = (pos & (~0x000FFF)) | tmpp | p1;
	dirc = (dir & (~0x00FF)) | tmpd | d1;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te11 = Eget_bits(E1,0); //get 1(1)
	E1 = Eclean_bits(E1,0) | Eget_bits(E3,0); //1(3) to 1(1)  
	E3 = Eclean_bits(E3,0) | (Eget_bits(E1,18) >> 18); //7(1) to 1(3)
	E1 = Eclean_bits(E1,18) | (Eget_bits(E3,12) << 6); //5(3) to 7(1)
	E3 = Eclean_bits(E3,12) | (te11 << 12); //1(1) to 5(3)
	Uint te21 = Eget_bits(E2,0);
	E2 = (E2 & 0xFFF000) | ((E2 & 0x000FF8) >> 3) | (te21 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}


//////////////////////////   Down   //////////////////////////
void Xube_State::rotate_down () {

	Uint pos = posc,dir = dirc;
	Uint p5 = ((0x7 << 12) & pos) << 9; //get pos 5
	Uint d5 = ((0x3 << 8) & dir) << 6; //get dir 5
	Uint tmpp = (0xFF8000 & pos) >> 3; //get pos 6,7,8
	Uint tmpd = (0xFC00 & dir) >> 2; //get dir 6,7,8
	posc = (pos & (~0xFFF000)) | tmpp | p5;
	dirc = (dir & (~0xFF00)) | tmpd | d5;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te13 = Eget_bits(E1,6); //get 3(1)
	E1 = Eclean_bits(E1,6) | Eget_bits(E3,6); //3(3) to 3(1)  
	E3 = Eclean_bits(E3,6) | (Eget_bits(E1,12) >> 6); //5(1) to 3(3) 
	E1 = Eclean_bits(E1,12) | (Eget_bits(E3,18) >> 6); //7(3) to 5(1)
	E3 = Eclean_bits(E3,18) | (te13 << 12); //3(1) to 7(3)
	Uint te28 = Eget_bits(E2,21);
	E2 = (E2 & 0x000FFF) | ((E2 & 0x1FF000) << 3) | (te28 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}

void Xube_State::rotate_down_ () {

	Uint pos = posc,dir = dirc;
	Uint p8 = ((0x7 << 21) & pos) >> 9; //get pos 8
	Uint d8 = ((0x3 << 14) & dir) >> 6; //get dir 8
	Uint tmpp = (0x1FF000 & pos) << 3; //get pos 5,6,7
	Uint tmpd = (0x3F00 & dir) << 2; //get dir 5,6,7
	posc = (pos & (~0xFFF000)) | tmpp | p8;
	dirc = (dir & (~0xFF00)) | tmpd | d8;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te13 = Eget_bits(E1,6); //get 3(1)
	E1 = Eclean_bits(E1,6) | (Eget_bits(E3,18) >> 12); //7(3) to 3(1)  
	E3 = Eclean_bits(E3,18) | (Eget_bits(E1,12) << 6); //5(1) to 7(3) 
	E1 = Eclean_bits(E1,12) | (Eget_bits(E3,6) << 6); //3(3) to 5(1)
	E3 = Eclean_bits(E3,6) | te13; //3(1) to 3(3)
	Uint te25 = Eget_bits(E2,12);
	E2 = (E2 & 0x000FFF) | ((E2 & 0xFF8000) >> 3) | (te25 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}


//////////////////////////   Left   ///////////////////////////

void Xube_State::rotate_left() {
	Uint pos = posc,dir = dirc;
	Uint p1 = Pget_bits(0); //get pos 1	
	Uint d1 = Dget_bits(0); //get dir 1

	pos = Pclean_bits(0) | (Pget_bits(12) >> 12); //from 5 to 1
	pos = Pclean_bits(12) | (Pget_bits(21) >> 9); //from 8 to 5
	pos = Pclean_bits(21) | (Pget_bits(9) << 12); //from 4 to 8
	pos = Pclean_bits(9) | (p1 << 9);

	dir = Dclean_bits(0) | (Dget_bits(8) >> 8); //from 5 to 1
	dir = Dclean_bits(8) | (Dget_bits(14) >> 6); //from 8 to 5
	dir = Dclean_bits(14) | (Dget_bits(6) << 8); //from 4 to 8
	dir = Dclean_bits(6) | (d1 << 6);

	rotate_dir(0x03C0,dir);
	rotate_dir(0xC003,dir);
	rotate_dir(0xC003,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te14 = Eget_bits(E1,9); //get 4(1)
	E1 = Eclean_bits(E1,9) | Eget_bits(E2,9); //4(2) to 4(1)  
	E2 = Eclean_bits(E2,9) | (Eget_bits(E1,21) >> 12); //8(1) to 4(2) 
	E1 = Eclean_bits(E1,21) | Eget_bits(E2,21); //8(2) to 8(1)
	E2 = Eclean_bits(E2,21) | (te14 << 12); //4(1) to 8(2)
	Uint te34 = Eget_bits(E3,9);
	E3 = (E3 & 0xFFF000) | ((E3 & 0x0001FF) << 3) | (te34 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}

void Xube_State::rotate_left_() {
	Uint pos = posc,dir = dirc;
	Uint p1 = Pget_bits(0); //get pos 1	
	Uint d1 = Dget_bits(0); //get dir 1

	pos = Pclean_bits(0) | (Pget_bits(9) >> 9); //from 4 to 1
	pos = Pclean_bits(9) | (Pget_bits(21) >> 12); //from 8 to 4
	pos = Pclean_bits(21) | (Pget_bits(12) << 9); //from 5 to 8
	pos = Pclean_bits(12) | (p1 << 12);

	dir = Dclean_bits(0) | (Dget_bits(6) >> 6); //from 4 to 1
	dir = Dclean_bits(6) | (Dget_bits(14) >> 8); //from 8 to 4
	dir = Dclean_bits(14) | (Dget_bits(8) << 6); //from 5 to 8
	dir = Dclean_bits(8) | (d1 << 8);

	rotate_dir(0x03C0,dir);
	rotate_dir(0xC003,dir);
	rotate_dir(0xC003,dir);

	posc = pos; dirc = dir;

	////////////////
	
	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te14 = Eget_bits(E1,9); //get 4(1)
	E1 = Eclean_bits(E1,9) | (Eget_bits(E2,21) >> 12); //8(2) to 4(1) 
	E2 = Eclean_bits(E2,21) | Eget_bits(E1,21); //8(1) to 8(2) 
	E1 = Eclean_bits(E1,21) | (Eget_bits(E2,9) << 12); //4(2) to 8(1)
	E2 = Eclean_bits(E2,9) | te14; //4(1) to 4(2)
	Uint te31 = Eget_bits(E3,0);
	E3 = (E3 & 0xFFF000) | ((E3 & 0x000FF8) >> 3) | (te31 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}


///////////////////////////   Right   //////////////////////////

void Xube_State::rotate_right() {
	Uint pos = posc,dir = dirc;
	Uint p2 = Pget_bits(3); //get pos 2
	Uint d2 = Dget_bits(2); //get dir 2

	pos = Pclean_bits(3) | (Pget_bits(6) >> 3); //from 3 to 2
	pos = Pclean_bits(6) | (Pget_bits(18) >> 12); //from 7 to 3
	pos = Pclean_bits(18) | (Pget_bits(15) << 3); //from 6 to 7
	pos = Pclean_bits(15) | (p2 << 12);

	dir = Dclean_bits(2) | (Dget_bits(4) >> 2); //from 3 to 2
	dir = Dclean_bits(4) | (Dget_bits(12) >> 8); //from 7 to 3
	dir = Dclean_bits(12) | (Dget_bits(10) << 2); //from 6 to 7
	dir = Dclean_bits(10) | (d2 << 8);

	rotate_dir(0x300C,dir);
	rotate_dir(0x0C30,dir);
	rotate_dir(0x0C30,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te12 = Eget_bits(E1,3); //get 2(1)
	E1 = Eclean_bits(E1,3) | (Eget_bits(E2,15) >> 12); //6(2) to 2(1)  
	E2 = Eclean_bits(E2,15) | Eget_bits(E1,15); //6(1) to 6(2) 
	E1 = Eclean_bits(E1,15) | (Eget_bits(E2,3) << 12); //2(2) to 6(1)
	E2 = Eclean_bits(E2,3) | te12; //2(1) to 2(2)
	Uint te38 = Eget_bits(E3,21);
	E3 = (E3 & 0x000FFF) | ((E3 & 0x1FF000) << 3) | (te38 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}


void Xube_State::rotate_right_() {
	Uint pos = posc,dir = dirc;
	Uint p2 = Pget_bits(3); //get pos 2
	Uint d2 = Dget_bits(2); //get dir 2

	pos = Pclean_bits(3) | (Pget_bits(15) >> 12); //from 6 to 2
	pos = Pclean_bits(15) | (Pget_bits(18) >> 3); //from 7 to 6
	pos = Pclean_bits(18) | (Pget_bits(6) << 12); //from 3 to 7
	pos = Pclean_bits(6) | (p2 << 3);

	dir = Dclean_bits(2) | (Dget_bits(10) >> 8); //from 6 to 2
	dir = Dclean_bits(10) | (Dget_bits(12) >> 2); //from 7 to 6
	dir = Dclean_bits(12) | (Dget_bits(4) << 8); //from 3 to 7
	dir = Dclean_bits(4) | (d2 << 2);

	rotate_dir(0x300C,dir);
	rotate_dir(0x0C30,dir);
	rotate_dir(0x0C30,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te12 = Eget_bits(E1,3); //get 2(1)
	E1 = Eclean_bits(E1,3) | Eget_bits(E2,3); //2(2) to 2(1)  
	E2 = Eclean_bits(E2,3) | (Eget_bits(E1,15) >> 12); //6(1) to 2(2) 
	E1 = Eclean_bits(E1,15) | Eget_bits(E2,15); //6(2) to 6(1)
	E2 = Eclean_bits(E2,15) | (te12 << 12); //2(1) to 6(2)

	Uint te35 = Eget_bits(E3,12);
	E3 = (E3 & 0x000FFF) | ((E3 & 0xFF8000) >> 3) | (te35 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}

////////////////////////   Front   ////////////////////////////

void Xube_State::rotate_front() {
	Uint pos = posc,dir = dirc;
	Uint p4 = Pget_bits(9); //get pos 4
	Uint d4 = Dget_bits(6); //get dir 4

	pos = Pclean_bits(9) | (Pget_bits(21) >> 12); //from 8 to 4
	pos = Pclean_bits(21) | (Pget_bits(18) << 3); //from 7 to 8
	pos = Pclean_bits(18) | (Pget_bits(6) << 12); //from 3 to 7
	pos = Pclean_bits(6) | (p4 >> 3); //from 4 to 3

	dir = Dclean_bits(6) | (Dget_bits(14) >> 8); //from 8 to 4
	dir = Dclean_bits(14) | (Dget_bits(12) << 2); //from 7 to 8
	dir = Dclean_bits(12) | (Dget_bits(4) << 8); //from 3 to 7
	dir = Dclean_bits(4) | (d4 >> 2); //from 4 to 3

	rotate_dir(0xC030,dir);
	rotate_dir(0x30C0,dir);
	rotate_dir(0x30C0,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te23 = Eget_bits(E2,6); //get 3(2)
	E2 = Eclean_bits(E2,6) | (Eget_bits(E3,3) << 3); //2(3) to 3(2)
	E3 = Eclean_bits(E3,3) | (Eget_bits(E2,12) >> 9); //5(2) to 2(3) 
	E2 = Eclean_bits(E2,12) | (Eget_bits(E3,21) >> 9); //8(3) to 5(2)
	E3 = Eclean_bits(E3,21) | (te23 << 15); //3(2) to 8(3)
	Uint te14 = Eget_bits(E1,9);
	E1 = (E1 & 0xFFF000) | ((E1 & 0x0001FF) << 3) | (te14 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}

void Xube_State::rotate_front_() {
	Uint pos = posc,dir = dirc;
	Uint p4 = Pget_bits(9); //get pos 4
	Uint d4 = Dget_bits(6); //get dir 4

	pos = Pclean_bits(9) | (Pget_bits(6) << 3); //from 3 to 4
	pos = Pclean_bits(6) | (Pget_bits(18) >> 12); //from 7 to 3
	pos = Pclean_bits(18) | (Pget_bits(21) >> 3); //from 8 to 7
	pos = Pclean_bits(21) | (p4 << 12); //from 4 to 8

	dir = Dclean_bits(6) | (Dget_bits(4) << 2); //from 3 to 4
	dir = Dclean_bits(4) | (Dget_bits(12) >> 8); //from 7 to 3
	dir = Dclean_bits(12) | (Dget_bits(14) >> 2); //from 8 to 7
	dir = Dclean_bits(14) | (d4 << 8); //from 4 to 8

	rotate_dir(0xC030,dir);
	rotate_dir(0x30C0,dir);
	rotate_dir(0x30C0,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te23 = Eget_bits(E2,6); //get 3(2)
	E2 = Eclean_bits(E2,6) | (Eget_bits(E3,21) >> 15); //8(3) to 3(2)
	E3 = Eclean_bits(E3,21) | (Eget_bits(E2,12) << 9); //5(2) to 8(3) 
	E2 = Eclean_bits(E2,12) | (Eget_bits(E3,3) << 9); //2(3) to 5(2)
	E3 = Eclean_bits(E3,3) | (te23 >> 3); //3(2) to 2(3)
	Uint te11 = Eget_bits(E1,0);
	E1 = (E1 & 0xFFF000) | ((E1 & 0x000FF8) >> 3) | (te11 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}


//////////////////////////   Back   //////////////////////////

void Xube_State::rotate_back() {
	Uint pos = posc,dir = dirc;
	Uint p2 = Pget_bits(0); //get pos 1
	Uint d2 = Dget_bits(0); //get dir 1

	pos = Pclean_bits(0) | (Pget_bits(3) >> 3); //from 2 to 1
	pos = Pclean_bits(3) | (Pget_bits(15) >> 12); //from 6 to 2
	pos = Pclean_bits(15) | (Pget_bits(12) << 3); //from 5 to 6
	pos = Pclean_bits(12) | (p2 << 12); //from 1 to 5

	dir = Dclean_bits(0) | (Dget_bits(2) >> 2); //from 2 to 1
	dir = Dclean_bits(2) | (Dget_bits(10) >> 8); //from 6 to 2
	dir = Dclean_bits(10) | (Dget_bits(8) << 2); //from 5 to 6
	dir = Dclean_bits(8) | (d2 << 8); //from 1 to 5

	rotate_dir(0x0C03,dir);
	rotate_dir(0x030C,dir);
	rotate_dir(0x030C,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te21 = Eget_bits(E2,0); //get 1(2)
	E2 = Eclean_bits(E2,0) | (Eget_bits(E3,15) >> 15); //6(3) to 1(2)
	E3 = Eclean_bits(E3,15) | (Eget_bits(E2,18) >> 3); //7(2) to 6(3) 
	E2 = Eclean_bits(E2,18) | (Eget_bits(E3,9) << 9); //4(3) to 7(2)
	E3 = Eclean_bits(E3,9) | (te21 << 9); //1(2) to 4(3)
	Uint te18 = Eget_bits(E1,21);
	E1 = (E1 & 0x000FFF) | ((E1 & 0x1FF000) << 3) | (te18 >> 9);
	e1 = E1; e2 = E2; e3 = E3;
}


void Xube_State::rotate_back_() {
	Uint pos = posc,dir = dirc;
	Uint p2 = Pget_bits(0); //get pos 1
	Uint d2 = Dget_bits(0); //get dir 1

	pos = Pclean_bits(0) | (Pget_bits(12) >> 12); //from 5 to 1
	pos = Pclean_bits(12) | (Pget_bits(15) >> 3); //from 6 to 5
	pos = Pclean_bits(15) | (Pget_bits(3) << 12); //from 2 to 6
	pos = Pclean_bits(3) | (p2 << 3); //from 1 to 2

	dir = Dclean_bits(0) | (Dget_bits(8) >> 8); //from 5 to 1
	dir = Dclean_bits(8) | (Dget_bits(10) >> 2); //from 6 to 5
	dir = Dclean_bits(10) | (Dget_bits(2) << 8); //from 2 to 6
	dir = Dclean_bits(2) | (d2 << 2); //from 1 to 2

	rotate_dir(0x0C03,dir);
	rotate_dir(0x030C,dir);
	rotate_dir(0x030C,dir);

	posc = pos; dirc = dir;

	////////////////

	Uint E1 = e1,E2 = e2,E3 = e3;
	Uint te21 = Eget_bits(E2,0); //get 1(2)
	E2 = Eclean_bits(E2,0) | (Eget_bits(E3,9) >> 9); //4(3) to 1(2)
	E3 = Eclean_bits(E3,9) | (Eget_bits(E2,18) >> 9); //7(2) to 4(3) 
	E2 = Eclean_bits(E2,18) | (Eget_bits(E3,15) << 3); //6(3) to 7(2)
	E3 = Eclean_bits(E3,15) | (te21 << 15); //1(2) to 6(3)
	Uint te15 = Eget_bits(E1,12);
	E1 = (E1 & 0x000FFF) | ((E1 & 0xFF8000) >> 3) | (te15 << 9);
	e1 = E1; e2 = E2; e3 = E3;
}


////////////////////////////////////////////////////////
/*
 * vim:foldmethod=marker
 */
