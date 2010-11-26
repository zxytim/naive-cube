#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/freeglut.h>
#include <unistd.h>

#include <cstdio>
#include <cmath>

#include "libs/cube.h"

#define WINDOW_NAME "OpenGL Test"


#define ESCAPE				27
#define PAGE_UP				73
#define PAGE_DOWN			81
#define UP_ARROW			72
#define DOWN_ARROW			80
#define LEFT_ARROW			75
#define RIGHT_ARROW			77

#define windowWidth			800
#define windowHeight		600



GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

GLuint texture[1];

GLfloat mouseSensitivity = 0.12;
GLfloat sightLen = 100;


Point rot(0, 0, 0);
Point rotSpeed(0.1, 0.1, 0.1);
Point sightpos(0, 0, -sightLen);
Point pos(0, 0, 0);
GLfloat posMoveSpeed = 0.1;
Point normalv(0, 1, 0);

bool keys[256];


GLvoid LoadGLTextures()
{
	Image *image;

	image = (Image *) malloc(sizeof(Image));

	if (image == NULL)
	{
		printf("Error allocation space for image.\n");
		exit(0);
	}

	if (!ImageLoad("hello.bmp", image))
		exit(1);

	glGenTextures(1, &texture[0]);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image->sizeX, image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);

}


int window;

GLvoid InitGL()
{
	LoadGLTextures();
	glEnable(GL_TEXTURE_2D);


	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0.5);
}

GLvoid ReSizeGLScene(int width, int height)
{
	if (height == 0) height = 1;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}

GLvoid DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	gluLookAt(pos.x, pos.y, pos.z,
			sightpos.x, sightpos.y, sightpos.z,
			normalv.x, normalv.y, normalv.z);


	glTranslatef(0, 0.0, -6);

	glRotatef(rot.x, 1, 0, 0);
	glRotatef(rot.y, 0, 1, 0);
	glRotatef(rot.z, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);

	glNormal3f( 0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);

	glNormal3f( 0.0f, 0.0f,-1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);

	glNormal3f( 0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);

	glNormal3f( 0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);

	glNormal3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);

	glEnd();

	rot.x += rotSpeed.x;
	rot.y += rotSpeed.y;
	rot.z += rotSpeed.z;

	glutSwapBuffers();
}

GLvoid keyPressed(unsigned char key, int x, int y)
{
	Point dir = (sightpos - pos).unit();
	Point leftdir = CrossProduct(dir, normalv).unit();
	switch (key)
	{
		case ESCAPE:
			glutDestroyWindow(window);
			exit(0);
		case 'w':
		case 'W':
			pos = pos + dir * posMoveSpeed;
			sightpos = sightpos + dir * posMoveSpeed;
			break;
		case 's':
		case 'S':
			pos = pos - dir * posMoveSpeed;
			sightpos = sightpos - dir * posMoveSpeed;
			break;
		case 'a':
		case 'A':
			pos = pos - leftdir * posMoveSpeed;
			sightpos = sightpos - leftdir * posMoveSpeed;
			break;
		case 'd':
		case 'D':
			pos = pos + leftdir * posMoveSpeed;
			sightpos = sightpos + leftdir * posMoveSpeed;
			break;
	}
}

GLvoid specialKeyPressed(int key, int x, int y)
{
}

GLvoid mouseEvent(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_ALPHA | GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);

	window = glutCreateWindow(WINDOW_NAME);

	glutDisplayFunc(&DrawGLScene);

	//glutFullScreen();

	glutIdleFunc(&DrawGLScene);

	glutReshapeFunc(&ReSizeGLScene);

	glutIgnoreKeyRepeat(0);

	glutKeyboardFunc(&keyPressed);

	//glutKeyboardUpFunc();

	glutSpecialFunc(&specialKeyPressed);

	glutMouseFunc(mouseEvent);

	InitGL();

	glutMainLoop();

	return 0;
}

