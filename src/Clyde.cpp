#include "Clyde.h"
#include "ResourceManager.h"

#include "Utilities.h"
#include "PacMan.h"
#include "Map.h"

Clyde::Clyde(Game* game, const PacMan* pacMan) :
	Ghost(game), m_pacMan(pacMan)
{
	m_ghostHouse.emplace_back(12, 12);
	m_ghostHouse.emplace_back(12, 13);

	m_scatterPath.emplace_back(6, 23);
	m_scatterPath.emplace_back(5, 23);
	m_scatterPath.emplace_back(4, 23);
	m_scatterPath.emplace_back(3, 23);
	m_scatterPath.emplace_back(2, 23);
	m_scatterPath.emplace_back(2, 24);
	m_scatterPath.emplace_back(2, 25);
	m_scatterPath.emplace_back(3, 25);
	m_scatterPath.emplace_back(4, 25);
	m_scatterPath.emplace_back(5, 25);
	m_scatterPath.emplace_back(6, 25);
	m_scatterPath.emplace_back(7, 25);
	m_scatterPath.emplace_back(8, 25);
	m_scatterPath.emplace_back(9, 25);
	m_scatterPath.emplace_back(10, 25);
	m_scatterPath.emplace_back(10, 24);
	m_scatterPath.emplace_back(10, 23);
	m_scatterPath.emplace_back(9, 23);
	m_scatterPath.emplace_back(8, 23);
	m_scatterPath.emplace_back(8, 22);
	m_scatterPath.emplace_back(8, 21);
	m_scatterPath.emplace_back(8, 20);
	m_scatterPath.emplace_back(7, 20);
	m_scatterPath.emplace_back(6, 20);
	m_scatterPath.emplace_back(6, 21);
	m_scatterPath.emplace_back(6, 22);

	m_stateProperties[GhostState::GhostHouse] = GhostStateProperties(10.f, GhostState::ExitGhostHouse);
	m_stateProperties[GhostState::Eaten] = GhostStateProperties(20.f, GhostState::ExitGhostHouse);
	m_stateProperties[GhostState::ExitGhostHouse] = GhostStateProperties(20.f, GhostState::GlobalState);
	m_stateProperties[GhostState::Frightened] = GhostStateProperties(10.f, GhostState::GlobalState);
}

void Clyde::findChaseDirection()
{
	const auto distance = length(getPosition() - m_pacMan->getPosition());
	if(distance < 8 * BLOCK_WIDTH)
	{
		if(m_mapPosition != m_scatterPath[0])
		{
			goToTarget(m_scatterPath[0]);
		}
		else
		{
			m_path.mapPositions = m_scatterPath;
			m_path.positionIndex = 0;
			updateDirection();
		}
	}
	else
	{
		goToTarget(m_pacMan->getMapPosition());
	}
}

void Clyde::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("clyde", "resources/graphics/clyde_anim.png");
	m_sprite.setTexture(resourceManager->getTexture("clyde"));
}
