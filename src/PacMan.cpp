#include "PacMan.h"

#include "ResourceManager.h"
#include "Map.h"
#include "Point.h"

#include "Utilities.h"

PacMan::PacMan(Game* game) :
	Entity(game),
	m_movementSpeed(60.f)
{
}

void PacMan::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("pacman", "resources/graphics/pacman.png");
	m_sprite.setTexture(resourceManager->getTexture("pacman"));
}

void PacMan::update(float deltaTime)
{
	processInput();

	sf::Vector2f moveDirection;

	const auto directionDiff = m_direction + m_nextDirection;
	if(directionDiff.x == 0 && directionDiff.y == 0)
	{
		if(findDestination(m_nextDirection))
		{
			m_direction = m_nextDirection;
		}
	}
	
	const sf::Vector2f nextPosition = getPosition() + (static_cast<sf::Vector2f>(m_direction) * m_movementSpeed * deltaTime);
	if (length(getPosition() - m_destination) > 2.f)
	{
		setPosition(nextPosition);
	}
	else
	{
		setPosition(m_destination);
		if(findDestination(m_nextDirection))
		{
			m_direction = m_nextDirection;
		}
		else
		{
			findDestination(m_direction);
		}
	}
	
}

void PacMan::beginPlay()
{
	setPosition({ BLOCK_WIDTH, BLOCK_WIDTH });
	m_direction = sf::Vector2i(0, 1);
	m_nextDirection = m_direction;
	m_mapPosition = sf::Vector2i(1, 1);
	m_movementSpeed = 60.f;
	findDestination(m_direction);

	m_bEnableCollision = true;
	m_collisionRect.width = BLOCK_WIDTH;
	m_collisionRect.height = BLOCK_WIDTH;
	m_bDrawCollisionRect = true;
}

void PacMan::onCollision(Entity* otherEntity)
{
	auto *point = dynamic_cast<Point*>(otherEntity);
	if(point)
	{
		point->destroy();
	}
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

bool PacMan::findDestination(sf::Vector2i direction)
{
	const auto tilePosition = m_mapPosition + direction;
	
	if(map[tilePosition.y][tilePosition.x] == 0)
	{
		m_mapPosition = tilePosition;
		m_destination = sf::Vector2f(tilePosition.x * BLOCK_WIDTH, tilePosition.y * BLOCK_WIDTH);
		return true;
	}

	return false;
}
