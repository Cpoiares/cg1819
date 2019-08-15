#include <math.h>
#include "lights.h"

extern GLfloat aVisao;
extern GLfloat obsPini[];

/* luz de ambiente */
GLint dia = 1;
GLfloat intensidade = .6f;
GLfloat luzGlobalCorAmb[4] = {intensidade, intensidade, intensidade, 1.0}; //
GLfloat ambientePreto[] = {0, 0, 0, 0};

/* luz pontual no tecto */
GLint tecto = 1;
GLfloat Posicao[] = {50.0f, 50.0f, 50.0f};
GLfloat CorAmbiente[] = {1, 1, 1, 1};
GLfloat CorDifusa[] = {1, 1, 1, 1};
GLfloat atConst = 1;
GLfloat atLinear = 1;
GLfloat atQuadr = 1;

/* foco de luz (lanterna) */
GLint ligaFoco = 1;
GLfloat rFoco = 1.1, aFoco = aVisao;
GLfloat incH = 0.0, incV = 0.0;
GLfloat incMaxH = 0.5, incMaxV = 0.35;
GLfloat focoPini[] = {obsPini[0], obsPini[1], obsPini[2], 1.0};
GLfloat focoPfin[] = {obsPini[0] - rFoco * cos(aFoco), obsPini[1], obsPini[2] - rFoco *sin(aFoco), 1.0};
GLfloat focoDir[] = {focoPfin[0] - focoPini[0], 0, focoPfin[2] - focoPini[2]};
GLfloat focoExp = 10.0;
GLfloat focoCut = 60.0;
GLfloat focoCorDif[4] = {0.9, 0.9, 0.9, 1.0};
GLfloat focoCorEsp[4] = {1.0, 1.0, 1.0, 1.0};

void initLights()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	/* luz ambiente */
	if (dia)
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	}
	else
	{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientePreto);
	}

	/* luz pontual no tecto */
	glLightfv(GL_LIGHT0, GL_POSITION, Posicao);
	glLightfv(GL_LIGHT0, GL_AMBIENT, CorAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, CorDifusa);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, atConst);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, atLinear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, atQuadr);

	if (tecto)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	/* foco de luz (lanterna) */
	glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCut);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);

	if (ligaFoco)
	{
		glEnable(GL_LIGHT1);
	}
	else
	{
		glDisable(GL_LIGHT1);
	}
}