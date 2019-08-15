#ifndef _MATERIALS_H_
#define _MATERIALS_H_

#include <GL/glut.h>

enum Material
{
	m_esmerald,
	m_jade,
	m_obsidian,
	m_pearl,
	m_ruby,
	m_turquoise,
	m_brass,
	m_bronze,
	m_chrome,
	m_copper,
	m_gold,
	m_silver,
	m_blackPlastic,
	m_cyankPlastic,
	m_greenPlastic,
	m_redPlastic,
	m_whitePlastic,
	m_yellowPlastic,
	m_blackRubber,
	m_cyanRubber,
	m_greenRubber,
	m_redRubber,
	m_whiteRubber,
	m_yellowRubber,
};

void initMaterials(int material);

#endif