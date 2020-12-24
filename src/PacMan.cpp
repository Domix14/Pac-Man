#include "PacMan.h"

#include "ResourceManager.h"
#include "Map.h"
#include "Coin.h"
#include "PacManGame.h"

#include "Utilities.h"

PacMan::PacMan(Game* game) :
	Entity(game),
	START_POSITION({2,1}),
	START_DIRECTION({ 0,1 }),
	m_movementSpeed(60.f)
{
	m_bEnableCollision = true;
	m_collisionRect.width = BLOCK_WIDTH;
	m_collisionRect.height = BLOCK_WIDTH;
}

void PacMan::loadResources(ResourceManager* resourceManager)
{
	/*resourceManager->loadTexture("pacman", "resources/graphics/pacman.png");
	m_sprite.setTexture(resourceManager->getTexture("pacman"));*/

	resourceManager->loadTexture("pacman_anim", "resources/graphics/pacman_anim.png");
	/*m_sprite.setTexture(resourceManager->getTexture("pacman"));
	m_sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));*/
	m_sprite.setTexture(resourceManager->getTexture("pacman_anim"));

	m_animation.addRects("right", { sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30) });
	m_animation.addRects("up", { sf::IntRect(0, 30, 30, 30), sf::IntRect(30, 30, 30, 30) });
	m_animation.addRects("left", { sf::IntRect(0, 60, 30, 30), sf::IntRect(30, 60, 30, 30) });
	m_animation.addRects("down", { sf::IntRect(0, 90, 30, 30), sf::IntRect(30, 90, 30, 30) });
	m_animation.setFrameTime(0.4f);
	m_animation.setAnimation("down", m_sprite);
}

void PacMan::update(float deltaTime)
{
	processInput();
	m_animation.update(deltaTime, m_sprite);

	const auto directionDiff = m_direction + m_nextDirection;
	if(directionDiff.x == 0 && directionDiff.y == 0)
	{
		if(findDestination(m_nextDirection))
		{
			setDirection(m_nextDirection);
		}
	}
	
	const sf::Vector2f nextPosition = getPosition() + (static_cast<sf::Vector2f>(m_direction) * m_movementSpeed * deltaTime);
	if (length(nextPosition - m_destination) < length(getPosition() - m_destination))
	{
		setPosition(nextPosition);
	}
	else
	{
		setPosition(m_destination);
		if(findDestination(m_nextDirection))
		{
			setDirection(m_nextDirection);
		}
		else
		{
			findDestination(m_direction);
		}
	}
}

void PacMan::beginPlay()
{
	restart();
	findDestination(m_direction);
}

void PacMan::onCollision(Entity* otherEntity)
{
	auto *point = dynamic_cast<Coin*>(otherEntity);
	if(point)
	{
		point->destroy();
		auto* game = dynamic_cast<PacManGame*>(getGame());
		if (game)
		{
			game->addScore(10);
		}
	}
	else
	{
		auto* powerUp = dynamic_cast<PowerUp*>(otherEntity);
		if(powerUp)
		{
			powerUp->destroy();
			auto* game = dynamic_cast<PacManGame*>(getGame());
			if (game)
			{
				game->addScore(100);
				game->changeState(GameState::Frightened);
			}
		}
	}
}

void PacMan::changeAnimation()
{
	if (m_direction == sf::Vector2i(0, -1))
	{
		m_animation.setAnimation("up", m_sprite);
	}
	else if (m_direction == sf::Vector2i(1, 0))
	{
		m_animation.setAnimation("right", m_sprite);
	}
	else if (m_direction == sf::Vector2i(0, 1))
	{
		m_animation.setAnimation("down", m_sprite);
	}
	else if (m_direction == sf::Vector2i(-1, 0))
	{
		m_animation.setAnimation("left", m_sprite);
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

void PacMan::setDirection(sf::Vector2i newDirection)
{
	m_direction = newDirection;
	changeAnimation();
}

bool PacMan::findDestination(sf::Vector2i direction)
{
	if (map[m_mapPosition.y][m_mapPosition.x] == MapType::Teleport)
	{
		m_mapPosition -= sf::Vector2i(static_cast<int>(getMapMaxColumnIndex()), 0);
		m_mapPosition = abs(m_mapPosition);
		setPosition(getMapOffset() + sf::Vector2f{ m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH });
	}
	
	const auto tilePosition = m_mapPosition + direction;
	
	if(map[tilePosition.y][tilePosition.x] <= MapType::Teleport)
	{
		m_mapPosition = tilePosition;
		m_destination = getMapOffset() + sf::Vector2f(tilePosition.x * BLOCK_WIDTH, tilePosition.y * BLOCK_WIDTH);
		return true;
	}

	return false;
}

void PacMan::restart()
{
	m_mapPosition = START_POSITION;
	setPosition(getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));
	setDirection(START_DIRECTION);
	m_nextDirection = m_direction;
}

sf::Vector2i PacMan::getMapPosition() const
{
	return m_mapPosition;
}

sf::Vector2i PacMan::getDirection() const
{
	return m_direction;
}
