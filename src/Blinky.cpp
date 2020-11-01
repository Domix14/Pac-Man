#include "Blinky.h"

#include "Utilities.h"
#include "PacMan.h"

Blinky::Blinky(Game* game, const PacMan* pacMan) :
	Ghost(game), m_pacMan(pacMan)
{
	m_ghostHouse.emplace_back(11, 11);
	m_ghostHouse.emplace_back(10, 12);
	m_ghostHouse.emplace_back(10, 13);
	m_ghostHouse.emplace_back(11, 12);
	m_ghostHouse.emplace_back(11, 13);
	m_ghostHouse.emplace_back(12, 12);
	m_ghostHouse.emplace_back(12, 13);

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

sf::Vector2i Blinky::findChaseDirection()
{
	auto directions = findAvailableDirections();
	int bestIndex = -1;
	float bestDistance = 0.f;
	for(int i = 0;i < directions.size();i++)
	{
		if(bestIndex == -1)
		{
			bestIndex = i;
			bestDistance = length(static_cast<sf::Vector2f>(m_pacMan->getMapPosition() - (m_mapPosition + directions[i])));
		}
		else
		{
			const auto distance = length(static_cast<sf::Vector2f>(m_pacMan->getMapPosition() - (m_mapPosition + directions[i])));
			if(distance < bestDistance)
			{
				bestIndex = i;
				bestDistance = distance;
			}
		}
	}
	return directions[bestIndex];
}

void Blinky::beginPlay()
{
	restart();

	changeState(GhostState::GhostHouse);
}
