#include "Inky.h"

#include "ResourceManager.h"
#include "Utilities.h"
#include "PacMan.h"
#include "Map.h"


Inky::Inky(Game* game, const PacMan* pacMan, const Ghost* blinky) :
	Ghost(game), m_pacMan(pacMan), m_blinky(blinky)
{
	m_ghostHouse.emplace_back(11, 12);
	m_ghostHouse.emplace_back(10, 12);
	m_ghostHouse.emplace_back(10, 13);
	m_ghostHouse.emplace_back(11, 13);
	m_ghostHouse.emplace_back(12, 13);
	m_ghostHouse.emplace_back(12, 12);

	
	m_scatterPath.emplace_back(16, 21);
	m_scatterPath.emplace_back(16, 22);
	m_scatterPath.emplace_back(16, 23);
	m_scatterPath.emplace_back(17, 23);
	m_scatterPath.emplace_back(18, 23);
	m_scatterPath.emplace_back(19, 23);
	m_scatterPath.emplace_back(20, 23);
	m_scatterPath.emplace_back(20, 24);
	m_scatterPath.emplace_back(20, 25);
	m_scatterPath.emplace_back(19, 25);
	m_scatterPath.emplace_back(18, 25);
	m_scatterPath.emplace_back(17, 25);
	m_scatterPath.emplace_back(16, 25);
	m_scatterPath.emplace_back(15, 25);
	m_scatterPath.emplace_back(14, 25);
	m_scatterPath.emplace_back(13, 25);
	m_scatterPath.emplace_back(12, 25);
	m_scatterPath.emplace_back(12, 24);
	m_scatterPath.emplace_back(12, 23);
	m_scatterPath.emplace_back(13, 23);
	m_scatterPath.emplace_back(14, 23);
	m_scatterPath.emplace_back(14, 22);
	m_scatterPath.emplace_back(14, 21);
	m_scatterPath.emplace_back(14, 20);
	m_scatterPath.emplace_back(15, 20);
	m_scatterPath.emplace_back(16, 20);
}

void Inky::findChaseDirection()
{
	auto direction = m_blinky->getMapPosition() - m_pacMan->getMapPosition();
	goToTarget(m_pacMan->getMapPosition() - direction);
}


void Inky::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("inky", "resources/graphics/inky_anim.png");
	m_sprite.setTexture(resourceManager->getTexture("inky"));
}
