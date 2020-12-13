#include "Blinky.h"

#include "Utilities.h"
#include "PacMan.h"
#include "ResourceManager.h"

Blinky::Blinky(Game* game, const PacMan* pacMan) :
	Ghost(game), m_pacMan(pacMan)
{
	m_ghostHouse.emplace_back(11, 12);
	m_ghostHouse.emplace_back(10, 12);
	m_ghostHouse.emplace_back(10, 13);
	m_ghostHouse.emplace_back(11, 13);
	m_ghostHouse.emplace_back(12, 13);
	m_ghostHouse.emplace_back(12, 12);
	

	m_scatterPath.emplace_back(16, 1);
	m_scatterPath.emplace_back(17, 1);
	m_scatterPath.emplace_back(18, 1);
	m_scatterPath.emplace_back(19, 1);
	m_scatterPath.emplace_back(20, 1);
	m_scatterPath.emplace_back(20, 2);
	m_scatterPath.emplace_back(20, 3);
	m_scatterPath.emplace_back(20, 4);
	m_scatterPath.emplace_back(20, 5);
	m_scatterPath.emplace_back(19, 5);
	m_scatterPath.emplace_back(18, 5);
	m_scatterPath.emplace_back(17, 5);
	m_scatterPath.emplace_back(16, 5);
	m_scatterPath.emplace_back(16, 4);
	m_scatterPath.emplace_back(16, 3);
	m_scatterPath.emplace_back(16, 2);
}

void Blinky::findChaseDirection()
{
	goToTarget(m_pacMan->getMapPosition());
}



void Blinky::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("blinky", "resources/graphics/blinky.png");
	m_sprite.setTexture(resourceManager->getTexture("blinky"));
}
