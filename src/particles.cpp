#include <GL/gl.h>
#include <stdlib.h>
#include "particles.h"

#define MAX_PARTICLES 10000

/* Particles */
GLfloat particle_speed = -3.0;
GLfloat particle_slowdown = 0.5;
//GLfloat particle_zoom = -40.0;

/* Sistema de Particulas */

struct
{
	bool isAlive;
	GLfloat life;
	GLfloat fade;
	GLfloat r, g, b;
	GLfloat x, y, z;
	GLfloat speed;
	GLfloat gravity;
} particle_sys[MAX_PARTICLES];

void initParticle(int i)
{
	particle_sys[i].isAlive = true;
	particle_sys[i].life = 1.0;
	particle_sys[i].fade = GLfloat(rand() % 100 / 1000.0f + 0.003f);
	particle_sys[i].x = (GLfloat)(rand() % 400 - 200);
	particle_sys[i].y = (GLfloat)(rand() % 21 + 20);
	particle_sys[i].z = (GLfloat)(rand() % 400 - 200);
	particle_sys[i].r = 1.0;
	particle_sys[i].g = 0.0;
	particle_sys[i].b = 0.0;
	particle_sys[i].speed = particle_speed;
	particle_sys[i].gravity = -2.8;
}

void drawParticles()
{
	GLfloat x, y, z;

	for (int i = 0; i < MAX_PARTICLES; i += 2)
	{
		if (particle_sys[i].isAlive)
		{
			x = particle_sys[i].x;
			y = particle_sys[i].y;
			z = particle_sys[i].z;

			// Draw particle
			glColor3f(1.0, 1.0, 1.0);

			glBegin(GL_LINES);
			{
				glVertex3f(x, y, z);
				glVertex3f(x, y + 1, z);
			}
			glEnd();

			// move y
			particle_sys[i].y += particle_sys[i].speed / (particle_slowdown * 1000);
			particle_sys[i].speed += particle_sys[i].gravity;
			// Life decay
			particle_sys[i].life -= particle_sys[i].fade;

			if (particle_sys[i].y <= 0.0)
			{
				particle_sys[i].life = -1.0;
				particle_sys[i].isAlive = false;
			}
			/* Revive in case of dead */
			if (!particle_sys[i].isAlive)
			{
				initParticle(i);
			}
		}
	}
}

void initParticles()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		initParticle(i);
	}
}