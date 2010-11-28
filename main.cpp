#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>

#include <unistd.h>
#include <cstdio>
#include <cmath>

#include "cube.h"

#define GAME_NAME "Naive Cube"

/* --------- Structures --------- */
typedef void (*GameStateCallback)();

/* --------- Settings ----------- */
GLfloat mouseSensitivity = 0.12;


/* ---------- Consts ------------ */
const Vector x_axis(1, 0, 0),
	  y_axis(0, 1, 0),
	  z_axis(0, 0, 1);

/* --------- Variables ---------- */

// game
int game_state					= GAME_STATE_RUN,
	FPS							= 60;

// cube and observer
Vector cube_pos					= Point(0, 0, -6),
	   cube_front_dir			= z_axis,
	   cube_up_dir				= y_axis,

	   observer_pos				= Point(0, 0, 0),
	   observer_front_dir		= z_axis,
	   observer_up_dir			= y_axis;

// window
int window_width				= 800,
	window_height				= 600,
	window;

// color
Color background_color			= Color(0, 0, 0, 0);

/* -------- Function declarations ---------- */
void doCubeRotate(GLfloat x, GLfloat y);
void InitGL(int argc, char *argv[]);
void InitConfig();

// callbacks
// OpenGL callbacks
GLvoid cbDrawScene();
GLvoid cbIdle();
GLvoid cbReshape(int width, int height);
GLvoid cbKeyPressed(unsigned char key, int x, int y);
GLvoid cbKeyUp(unsigned char key, int x, int y);
GLvoid cbSpecialKeyPressed(int key, int x, int y);
GLvoid cbSpecialKeyUp(int key, int x, int y);
GLvoid cbMouseEvent(int button, int state, int x, int y);
GLvoid cbMouseMotion(int x, int y);
GLvoid cbMousePassiveMotion(int x, int y);

// game state callbacks
void cbGameInit();
void cbGameMenu();
void cbGameStarting();
void cbGameRun();
void cbGameExit();


int main(int argc, char *argv[])
{
	InitGL(argc, argv);

	glutMainLoop();

	return 0;
}

void doCubeRotate(GLfloat x, GLfloat y)
{
	vector_rotate(cube_front_dir, y_axis, x);
	vector_rotate(cube_up_dir, y_axis, x);

	vector_rotate(cube_front_dir, x_axis, y);
	vector_rotate(cube_up_dir, x_axis, y);
#ifdef DEBUG
	printf("cube front dir: (%.3lf,%.3lf,%.3lf)\n", cube_front_dir.x, cube_front_dir.y, cube_front_dir.z);
	printf("cube up dir: (%.3lf,%.3lf,%.3lf)\n", cube_up_dir.x, cube_up_dir.y, cube_up_dir.z);
	printf("angle between front and up dir: %.3lf deg\n", get_angle(cube_front_dir, cube_up_dir));
#endif
}

void InitGL(int argc, char *argv[])
{
	InitConfig();

	/* window settings */
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_ALPHA | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(window_width, window_height);

	glutInitWindowPosition(0, 0);

	window = glutCreateWindow(GAME_NAME);


	/* display settings */
	glutDisplayFunc(cbDrawScene);

	glutIdleFunc(cbIdle);

	glutReshapeFunc(cbReshape);

	/* keyboard event callbacks */
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glutKeyboardFunc(cbKeyPressed);

	glutKeyboardUpFunc(cbKeyUp);

	glutSpecialFunc(cbSpecialKeyPressed);

	glutSpecialUpFunc(cbSpecialKeyUp);

	/* mouse event callbacks */
	glutMouseFunc(cbMouseEvent);

	glutMotionFunc(cbMouseMotion);

	glutPassiveMotionFunc(cbMousePassiveMotion);



	glClearColor(background_color.r, background_color.g, background_color.g, background_color.a);

	glDepthFunc(GL_LESS);
	
	glEnable(GL_DEPTH_TEST);

	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);

	gluPerspective(45.0, (GLfloat)window_width / (GLfloat)window_height, 0.1, 100.0);
}

void InitConfig()
{
}


GLvoid cbDrawScene()
{
	static GameStateCallback cb_game_state[] =
	{
		cbGameInit,
		cbGameMenu,
		cbGameStarting,
		cbGameRun,
		cbGameExit
	};

	cb_game_state[game_state]();

	glutSwapBuffers();

	return;
}

GLvoid cbIdle()
{
	if (timeEnd(TIME_UNIT_MS) * FPS < 1000)
	{
		usleep(1000 / FPS / 2);
		return;
	}

	cbDrawScene();

	timeStart();
}

GLvoid cbReshape(int width, int height)
{
	if (height == 0)
		height == 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}

GLvoid cbKeyPressed(unsigned char key, int x, int y)
{
}

GLvoid cbKeyUp(unsigned char key, int x, int y)
{
}

GLvoid cbSpecialKeyPressed(int key, int x, int y)
{
}

GLvoid cbSpecialKeyUp(int key, int x, int y)
{
}

GLvoid cbMouseEvent(int button, int state, int x, int y)
{
}

GLvoid cbMouseMotion(int x, int y)
{
}

GLvoid cbMousePassiveMotion(int x, int y)
{
}


void cbGameInit()
{
}

void cbGameMenu()
{
}

void cbGameStarting()
{
}

void cbGameRun()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0, 0, -6);	

	glBegin(GL_LINES);

	glColor3f(1, 1, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 1, 1);

	glEnd();
}

void cbGameExit()
{
}


