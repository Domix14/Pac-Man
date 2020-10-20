#include "PacMan.h"

#include "ResourceManager.h"
#include "Map.h"

#include <iostream>

#include "Utilities.h"

PacMan::PacMan(Game* game) :
	Entity(game)
{
}

void PacMan::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("test", "image.png");
	m_sprite.setTexture(resourceManager->getTexture("test"));
}

void PacMan::update(float deltaTime)
{
	processInput();

	sf::Vector2f moveDirection;

	sf::Vector2i directionDiff = m_direction + m_nextDirection;
	if(directionDiff.x == 0 && directionDiff.y == 0)
	{
		if(findDestination(m_nextDirection, m_destination))
		{
			m_direction = m_nextDirection;
		}
	}
	
	sf::Vector2f nextPosition = getPosition() + (static_cast<sf::Vector2f>(m_direction) * m_movementSpeed * deltaTime);
	if (length(getPosition() - m_destination) > 2.f)
	{
		setPosition(nextPosition);
	}
	else
	{
		setPosition(m_destination);
		if(findDestination(m_nextDirection, m_destination))
		{
			m_direction = m_nextDirection;
		}
		else
		{
			m_nextDirection = m_direction;
		}
	}
	
}

void PacMan::beginPlay()
{
	setPosition({ 80.f, 80.f });
	m_direction = sf::Vector2i(0.f, 1);
	m_nextDirection = m_direction;
	m_movementSpeed = 60.f;
	findDestination(m_direction, m_destination);
}

void PacMan::processInput()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_nextDirection != sf::Vector2i(0, -1))
	{
		m_nextDirection = sf::Vector2i(0, -1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_nextDirection != sf::Vector2i(1, 0))
	{
		m_nextDirection = sf::Vector2i(1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_nextDirection != sf::Vector2i(0, 1))
	{
		m_nextDirection = sf::Vector2i(0, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_nextDirection != sf::Vector2i(-1, 0))
	{
		m_nextDirection = sf::Vector2i(-1, 0);
	}
}

bool PacMan::findDestination(sf::Vector2i direction, sf::Vector2f& destination)
{
	const sf::Vector2i startTilePosition = static_cast<sf::Vector2i>(getPosition() / 80.f);
	auto tilePosition = startTilePosition;
	
	

	//Check if index is in range
	auto checkIndexRange = [](const sf::Vector2i& indexes) {return !(indexes.x > 9 || indexes.x < 0 || indexes.y > 9 || indexes.y < 0); };

	bool bFound = false;
	do
	{
		
		tilePosition += direction;

		
		if (!checkIndexRange(tilePosition)) return false;

		if(map[tilePosition.y][tilePosition.x] == 1)
		{
			tilePosition -= direction;
			if(tilePosition != startTilePosition)
			{
				destination = sf::Vector2f(tilePosition.x * 80.f, tilePosition.y * 80.f);
				return true;
			}

			return false;
		}

		int routesCount = 0;

		auto nextTilePosition{ tilePosition + sf::Vector2i(0, -1) };
		if (checkIndexRange(nextTilePosition) && map[nextTilePosition.y][nextTilePosition.x] != 1)
		{
			routesCount++;
		}

		nextTilePosition =  tilePosition + sf::Vector2i(1, 0) ;
		if (checkIndexRange(nextTilePosition) && map[nextTilePosition.y][nextTilePosition.x] != 1)
		{
			routesCount++;
		}

		nextTilePosition = tilePosition + sf::Vector2i(0, 1);
		if (checkIndexRange(nextTilePosition) && map[nextTilePosition.y][nextTilePosition.x] != 1)
		{
			routesCount++;
		}

		nextTilePosition = tilePosition + sf::Vector2i(-1, 0);
		if (checkIndexRange(nextTilePosition) && map[nextTilePosition.y][nextTilePosition.x] != 1)
		{
			routesCount++;
		}

		if (routesCount > 2 || routesCount == 1) bFound = true;
		
	} while (!bFound);

	
	
	destination = sf::Vector2f(tilePosition.x * 80.f, tilePosition.y * 80.f);

	LOG("Destination: ", m_destination);
	LOG("Direction", static_cast<sf::Vector2f>(direction));
	
	return true;
}
