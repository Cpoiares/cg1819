#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <GL/glut.h>

#ifdef _WIN32
#include "windows.h"
#endif

#include "input.h"
#include "loader.h"
#include "materials.h"
#include "lights.h"
#include "particles.h"
#include "cube.h"
#include "RgbImage.h"

using namespace std;

#define PI 3.14159

/* ficheiros */
#define STAIRS_M_FILENAME "./models/seg_notexture.obj"
#define SKYBOX_T_FILENAME "./textures/skybox.bmp"
#define FLOOR_T_FILENAME "./textures/floor.bmp"
#define LAKE_T_FILENAME "./textures/lake.bmp"
#define MOON_T_FILENAME "./textures/moon.bmp"
#define WOOD_T_FILENAME "./textures/wood.bmp"

/* indice de texturas */
enum
{
	it_skybox,
	it_floor,
	it_lake,
	it_moon,
	it_wood,
};

int elapsedTime = 0;

GLint wScreen = 800, hScreen = 600;
GLfloat xC = 16.0, yC = 10.0, zC = 15.0;
GLfloat rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat obsPini[] = {-10, 5, 0};
GLfloat obsPfin[] = {obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao *sin(aVisao)};
GLfloat D[] = {0, 0, 0};
GLfloat angPersp = 109.0;
GLfloat angZoom = 63;
GLfloat incZoom = 3;
GLfloat tam = 2.0;
vector<GLfloat> vertices;
vector<GLfloat> cores;
vector<GLfloat> normais;
vector<vector<GLuint>> faces;

/* skybox */
GLUquadricObj *sky = gluNewQuadric();

/* moon */
GLUquadricObj *moon = gluNewQuadric();

/* texturas */
GLuint texture[10];
RgbImage imag;

/* materiais */
GLint material = 10;

void initTexturas()
{
	//----------------------------------------- Sky
	glGenTextures(1, &texture[it_skybox]);
	glBindTexture(GL_TEXTURE_2D, texture[it_skybox]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile(SKYBOX_T_FILENAME);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Floor
	glGenTextures(1, &texture[it_floor]);
	glBindTexture(GL_TEXTURE_2D, texture[it_floor]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile(FLOOR_T_FILENAME);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Lake
	glGenTextures(1, &texture[it_lake]);
	glBindTexture(GL_TEXTURE_2D, texture[it_lake]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile(LAKE_T_FILENAME);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Moon
	glGenTextures(1, &texture[it_moon]);
	glBindTexture(GL_TEXTURE_2D, texture[it_moon]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile(MOON_T_FILENAME);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Wood
	glGenTextures(1, &texture[it_wood]);
	glBindTexture(GL_TEXTURE_2D, texture[it_wood]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile(WOOD_T_FILENAME);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());
}

void drawSkySphere()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(m_whitePlastic);
	glBindTexture(GL_TEXTURE_2D, texture[it_skybox]);

	glPushMatrix();
	{
		glRotatef(90, -1, 0, 0);
		gluQuadricDrawStyle(sky, GLU_FILL);
		gluQuadricNormals(sky, GLU_SMOOTH);
		gluQuadricTexture(sky, GL_TRUE);
		gluSphere(sky, 500 * 1, 150, 150);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawFloor()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(m_whitePlastic);
	glBindTexture(GL_TEXTURE_2D, texture[it_floor]);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(200, 0, 200);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-200, 0, 200);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-200, 0, -200);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(200, 0, -200);
	}
	glEnd();
}

void drawLake()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(m_silver);
	glBindTexture(GL_TEXTURE_2D, texture[it_lake]);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(125, 1, -25);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-15, 1, -25);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-15, 1, 25);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(125, 1, 25);
	}
	glEnd();
}

void drawMoon()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(m_whitePlastic);
	glBindTexture(GL_TEXTURE_2D, texture[it_moon]);

	GLfloat moonPosicao[] = {50.0f, 50.0f, 100.0f};

	glPushMatrix();
	{
		glRotatef((elapsedTime / 50) % 360, 0, 1, 0);
		glTranslatef(moonPosicao[0], moonPosicao[1], moonPosicao[2]);
		glRotatef(90, -1, 0, 0);
		gluQuadricDrawStyle(moon, GLU_FILL);
		gluQuadricNormals(moon, GLU_SMOOTH);
		gluQuadricTexture(moon, GL_TRUE);
		glRotatef(180, 1, 0, 0);
		gluSphere(moon, 10, 150, 150);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawStairs()
{
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initMaterials(m_whitePlastic);
	glPushMatrix();
	{
		glTranslatef(0, 0.5, 0);
		for (int i = 0; i < 50; i++)
		{
			glTranslatef(1, 1, 0);
			glPushMatrix();
			{
				glScalef(1, 1, 10);
				drawCube(1, texture[it_wood]);
			}
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void drawTorus()
{
	glColor3f(1, 1, 1);
	initMaterials(material);
	glPushMatrix();
	{
		glTranslatef(0, 10, -10);
		glRotatef((elapsedTime / 10) % 360, 1, 0, 1);
		glutSolidTorus(2.0, 5.0, 50, 60);
	}
	glPopMatrix();
}

void drawReflection()
{
	// slide
	glColorMask(0, 0, 0, 0);  // Não escreve no colorBuf
	glDisable(GL_DEPTH_TEST); // nao considear profundidade

	glEnable(GL_STENCIL_TEST);		// Usar StencilBuf
	glClear(GL_STENCIL_BUFFER_BIT); // Garantir que está a zeros
	glStencilMask(0xFF);			// Define valores a escrever 1=(0xFF)

	glStencilFunc(GL_ALWAYS, 1, 1);					 // passa sempre teste
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); // substitui por ref=1
	drawLake();

	// slide
	glColorMask(1, 1, 1, 1);	  // Escrever colorBuffer
	glEnable(GL_DEPTH_TEST);	  // Enable Zbuffer
	glClear(GL_DEPTH_BUFFER_BIT); // Garantir apaga zbuffer

	glStencilFunc(GL_EQUAL, 1, 1);			// Desenha so na zona do StencilBuff
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); // Stencil fica igual !
	glPushMatrix();							//::: Transformação geométrica que implement o mirror
	{
		glScalef(1, -1, 1); // se plano Y=0
		drawMoon();
		drawStairs();
		drawTorus();
	}
	glPopMatrix();

	// slide
	glDisable(GL_STENCIL_TEST); // Disable stencilbuffer – desenhar em todo o lado
	drawMoon();
	drawStairs();
	drawTorus();

	// slide
	glEnable(GL_BLEND); // enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glColor4f(1, 1, 1, 0.3);
	drawLake();
	glDisable(GL_BLEND);
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glVertexPointer(3, GL_FLOAT, 0, &vertices.front());
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	initParticles();
	initTexturas();
	initLights();
	initMaterials(material);
	glNormalPointer(GL_FLOAT, 0, &normais.front());
	glEnableClientState(GL_NORMAL_ARRAY);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 300 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
	initLights();

	drawFloor();
	drawLake();
	drawSkySphere();
	// drawTorus();
	drawReflection();
	drawParticles();

	glutSwapBuffers();
}

void timer(int extra)
{
	elapsedTime = glutGet(GLUT_ELAPSED_TIME);
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}

GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	loadObj(STAIRS_M_FILENAME, vertices, normais, cores, faces);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GL_STENCIL_BUFFER_BIT);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("|Observador:'SETAS'|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
	return 0;
}
