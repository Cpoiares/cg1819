#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "input.h"

extern GLfloat rVisao, aVisao;
extern GLfloat obsP[];
extern GLfloat D[];
extern GLint wScreen, hScreen;
extern GLint material, dia, tecto, ligaFoco;
extern GLfloat focoPini[], focoPfin[], focoDir[], rFoco, aFoco, incMaxH, incMaxV;
extern GLfloat obsPini[], obsPfin[], incH, incV, angPersp, incVisao;

//=================================================================== EVENTOS
void updateVisao()
{
	obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
	obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);

	focoPini[0] = obsPini[0];
	focoPini[2] = obsPini[2];
	focoPfin[0] = focoPini[0] - rFoco * cos(aFoco + incH);
	focoPfin[2] = focoPini[2] - rFoco * sin(aFoco + incH);
	focoPini[1] = obsPini[1];
	focoPini[2] = obsPini[2];
	focoDir[0] = focoPfin[0] - focoPini[0];
	focoDir[1] = incV;
	focoDir[2] = focoPfin[2] - focoPini[2];
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'm':
	case 'M':
		material++;
		if (material > 23)
			material = 0;
		break;

	//--------------------------- Direccao da Lanterna
	//--------------------------- Projeccao
	case 's':
	case 'S':
		incH = incH - 0.05;
		if (incH < -incMaxH)
			incH = -incMaxH;
		updateVisao();
		break;
	case 'd':
	case 'D':
		incH = incH + 0.05;
		if (incH > incMaxH)
			incH = incMaxH;
		updateVisao();
		break;
	case 'e':
	case 'E':
		incV = incV + 0.05;
		if (incV > incMaxV)
			incV = incMaxV;
		updateVisao();
		break;
	case 'c':
	case 'C':
		incV = incV - 0.05;
		if (incV < -incMaxV)
			incV = -incMaxV;
		updateVisao();
		break;

	case 'f':
	case 'F':
		ligaFoco = !ligaFoco;
		break;

	//--------------------------- Angulo
	case 'z':
	case 'Z':
		angPersp = angPersp + 3;
		if (angPersp > 170)
			angPersp = 170;
		break;

	case 'x':
	case 'X':
		angPersp = angPersp - 3;
		if (angPersp < 1)
			angPersp = 1;
		break;

	//--------------------------- Altura observador
	case 'q':
	case 'Q':
		obsPini[1] = obsPini[1] + 1;
		break;

	case 'a':
	case 'A':
		obsPini[1] = obsPini[1] - 1;
		break;

	case 't':
	case 'T':
		tecto = !tecto;
		break;

	case 'n':
	case 'N':
		dia = !dia;
		break;

	case 27:
		exit(0);
		break;
	}

	std::cout << "dia: " << dia << std::endl;
	std::cout << "tecto: " << tecto << std::endl;
	std::cout << "foco: " << ligaFoco << std::endl;
	std::cout << "material: " << material << std::endl << std::endl;
}

void teclasNotAscii(int key, int x, int y)
{

	if (key == GLUT_KEY_UP)
	{
		obsPini[0] = obsPini[0] + 4 * (incVisao * cos(aVisao));
		obsPini[2] = obsPini[2] - 4 * (incVisao * sin(aVisao));
	}
	if (key == GLUT_KEY_DOWN)
	{
		obsPini[0] = obsPini[0] - 4 * incVisao * cos(aVisao);
		obsPini[2] = obsPini[2] + 4 * incVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)
	{
		aVisao = (aVisao + 0.1);
		aFoco = aFoco - 0.1;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		aVisao = (aVisao - 0.1);
		aFoco = aFoco + 0.1;
	}

	updateVisao();
}
