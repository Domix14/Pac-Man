#include "Blinky.h"

#include "Utilities.h"
#include "PacMan.h"
#include "ResourceManager.h"

Blinky::Blinky(Game* game, const PacMan* pacMan) :
	Ghost(game), m_pacMan(pacMan)
{
	m_ghostHouse.emplace_back(11, 12);
	m_ghostHouse.emplace_back(11, 13);
	
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

	m_stateProperties[GhostState::GhostHouse] = GhostStateProperties(0.f, GhostState::ExitGhostHouse);
	m_stateProperties[GhostState::Eaten] = GhostStateProperties(20.f, GhostState::ExitGhostHouse);
	m_stateProperties[GhostState::ExitGhostHouse] = GhostStateProperties(20.f, GhostState::GlobalState);
	m_stateProperties[GhostState::Frightened] = GhostStateProperties(10.f, GhostState::GlobalState);
}

void Blinky::findChaseDirection()
{
	goToTarget(m_pacMan->getMapPosition());
}

void Blinky::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("blinky", "resources/graphics/blinky_anim.png");
	m_sprite.setTexture(resourceManager->getTexture("blinky"));
}
