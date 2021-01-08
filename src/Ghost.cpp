#include "Ghost.h"

#include "ResourceManager.h"
#include "Map.h"
#include "Utilities.h"
#include "PacMan.h"

#include <algorithm>
#include <array>
#include <list>

sf::Vector2i Path::getNextMapPosition()
{
	//assert(!mapPositions.empty(), "Positions vector is empty!");
	const auto position = mapPositions[positionIndex];
	positionIndex = (++positionIndex) % mapPositions.size();
	return position;
}

void Path::addPosition(sf::Vector2i position)
{
	//if (!Ghost::checkPosition(position)) return;

	mapPositions.push_back(position);
	if(map[position.y][position.x] == MapType::Teleport)
	{
		position -= sf::Vector2i(static_cast<int>(getMapMaxColumnIndex()), 0);
		mapPositions.push_back(abs(position));
	}
}

Ghost::Ghost(Game* game) :
	Entity(game),
	START_POSITION({ 11,12 }),
	START_DIRECTION({ 0,1 }),
	MOVEMENT_SPEED(80.f),
	FAST_MOVEMENT_SPEED(400.f),
	SLOW_MOVEMENT_SPEED(40.f),
	m_path()
{
	m_collisionRect.width = 15;
	m_collisionRect.height = 15;
	m_collisionRectOffset = { 7.5f, 7.5f };
	m_bEnableCollision = true;

	m_animation.addRects("right", { sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30) });
	m_animation.addRects("up", { sf::IntRect(0, 30, 30, 30), sf::IntRect(30, 30, 30, 30) });
	m_animation.addRects("left", { sf::IntRect(0, 60, 30, 30), sf::IntRect(30, 60, 30, 30) });
	m_animation.addRects("down", { sf::IntRect(0, 90, 30, 30), sf::IntRect(30, 90, 30, 30) });
	m_animation.addRects("frightened", { sf::IntRect(0, 120, 30, 30), sf::IntRect(30, 120, 30, 30) });
	m_animation.setFrameTime(0.4f);
}

void Ghost::update(float deltaTime)
{
	updateStateTimer(deltaTime);
	m_animation.update(deltaTime, m_sprite);
	const sf::Vector2f nextPosition = getPosition() + (static_cast<sf::Vector2f>(m_direction) * m_movementSpeed * deltaTime);
	if (length(nextPosition - m_destination) < length(getPosition() - m_destination))
	{
		setPosition(nextPosition);
	}
	else 
	{
		setPosition(m_destination);
		if (m_path.positionIndex != 0)
		{
			updateDirection();
		}
		else
		{
			findNextPosition();
		}
	}
	
}

void Ghost::beginPlay()
{
	//findNextPosition();
}

void Ghost::onCollision(Entity* otherEntity)
{
	const auto pacMan = dynamic_cast<PacMan*>(otherEntity);
	if(pacMan)
	{
		if(m_ghostState == GhostState::Frightened)
		{
			changeState(GhostState::Eaten);
		}
	}
}

void Ghost::changeGlobalState(GhostState newState)
{
	m_globalGhostState = newState;
}

void Ghost::changeState(GhostState newState)
{
	if (m_ghostState == newState) return;

	m_ghostState = newState;
	m_stateTimer = m_stateProperties[m_ghostState].duration;

	if (m_ghostState == GhostState::GlobalState && map[m_mapPosition.y][m_mapPosition.x] == MapType::GhostHouse)
	{
		changeState(GhostState::ExitGhostHouse);
	}
	
	switch(m_ghostState)
	{
	case GhostState::Frightened:
		{
			m_animation.setAnimation("frightened", m_sprite);
			break;
		}
	case GhostState::Eaten:
		{
			m_movementSpeed = FAST_MOVEMENT_SPEED;
			//m_animation.setAnimation("frightened", m_sprite);
			break;
		}
	case GhostState::GhostHouse:
		{
			m_movementSpeed = MOVEMENT_SPEED;
			break;
		}
	default:
		{
			changeAnimation();
		}
	}
	
	
}

sf::Vector2i Ghost::getMapPosition() const
{
	return m_mapPosition;
}

void Ghost::updateDirection()
{
	const auto nextMapPosition = m_path.getNextMapPosition();
	if(length(static_cast<sf::Vector2f>(nextMapPosition - m_mapPosition)) > 1.f)
	{
		m_mapPosition = nextMapPosition;
		m_destination = getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH);
		setDirection(-m_direction);
		setPosition(getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));
	}
	else
	{
		setDirection(nextMapPosition - m_mapPosition);
		m_mapPosition = nextMapPosition;
		m_destination = getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH);		
	}

	if(map[m_mapPosition.y][m_mapPosition.x] == MapType::SlowDown || map[m_mapPosition.y][m_mapPosition.x] == MapType::Teleport)
	{
		m_movementSpeed = SLOW_MOVEMENT_SPEED;
	}
	else if (m_ghostState != GhostState::Eaten)
	{
		m_movementSpeed = MOVEMENT_SPEED;
	}
}

void Ghost::findNextPosition()
{
	GhostState state = m_ghostState;
	if(m_ghostState == GhostState::GlobalState)
	{
		state = m_globalGhostState;
	}
	
	switch(state)
	{
		case GhostState::Scatter:
		{
			if (m_mapPosition != m_scatterPath[0])
			{
				goToTarget(m_scatterPath[0]);
			}
			else
			{
				m_path.mapPositions = m_scatterPath;
				m_path.positionIndex = 0;
				updateDirection();
			}
			break;
		}
		
		case GhostState::Frightened:
		{
			auto directions = findAvailableDirections();

			if (!directions.empty())
			{
				const int index = randRange(0, static_cast<int>(directions.size() - 1));
				goToTarget(m_mapPosition + *(std::next(directions.begin(), index)));
			}
			break;
		}
		
		case GhostState::Chase:
		{
			findChaseDirection();
			break;
		}
		
		case GhostState::Eaten:
		{
			if (m_mapPosition != m_ghostHouse[0])
			{
				goToTarget(m_ghostHouse[0]);
			}
			else
			{
				changeState(GhostState::GhostHouse);
			}
			break;
		}

		case GhostState::GhostHouse:
		{
			if (m_mapPosition != m_ghostHouse[0] && m_mapPosition != m_ghostHouse[1])
			{
				goToTarget(m_ghostHouse[0]);
			}
			else if (m_mapPosition == m_ghostHouse[0])
			{
				goToTarget(m_ghostHouse[1]);
			}
			else if(m_mapPosition == m_ghostHouse[1])
			{
				goToTarget(m_ghostHouse[0]);
			}
			break;
		}
		case GhostState::ExitGhostHouse:
		{
			if (map[m_mapPosition.y][m_mapPosition.x] == MapType::GhostHouse)
			{
				goToTarget(sf::Vector2i(11, 10));
			}
			else
			{
				changeState(GhostState::GlobalState);
			}
			break;
		}
	}
}

void Ghost::setDirection(sf::Vector2i nextDirection)
{
	m_direction = nextDirection;
	changeAnimation();
}

void Ghost::changeAnimation()
{
	if (m_ghostState == GhostState::Frightened) return;

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


void Ghost::goToTarget(sf::Vector2i position)
{
	m_path.mapPositions.clear();
	m_path.positionIndex = 0;
	
	auto directions = findAvailableDirections();
	int bestIndex = -1;
	float bestDistance = 0.f;
	for (int i = 0; i < directions.size(); i++)
	{
		if (bestIndex == -1)
		{
			bestIndex = i;
			bestDistance = length(static_cast<sf::Vector2f>(position - (m_mapPosition + directions[i])));
		}
		else
		{
			const auto distance = length(static_cast<sf::Vector2f>(position - (m_mapPosition + directions[i])));
			if (distance < bestDistance)
			{
				bestIndex = i;
				bestDistance = distance;
			}
		}
	}

	m_path.addPosition(m_mapPosition + directions[bestIndex]);
	updateDirection();
}

bool Ghost::checkPosition(sf::Vector2i position) const
{
	if (position.x < 0 ||
		position.y < 0 ||
		position.x > getMapMaxColumnIndex() ||
		position.y > getMapMaxRowIndex())
	{
		return false;
	}

	
	if(map[position.y][position.x] <= MapType::GhostHouse &&
		(m_ghostState == GhostState::GhostHouse || m_ghostState == GhostState::ExitGhostHouse || m_ghostState == GhostState::Eaten)
		|| map[position.y][position.x] <= MapType::SlowDown)
	{
		return true;
	}
	return false;
}

std::vector<sf::Vector2i> Ghost::findAvailableDirections() const
{
	auto position = m_mapPosition;
	if(!m_path.mapPositions.empty())
	{
		position = m_path.mapPositions.back();
	}
	
	std::vector<sf::Vector2i> availableDirections{ { {0,-1}, {1,0}, {0,1}, {-1,0} } };
	for (auto it = availableDirections.begin(); it != availableDirections.end();)
	{
		if (*it == -m_direction || !checkPosition(position + *it))
		{
			it = availableDirections.erase(it);
		}
		else
		{
			++it;
		}
	}
	if(availableDirections.empty() || map[m_mapPosition.y][m_mapPosition.x] == MapType::GhostHouse)
	{
		availableDirections.push_back(-m_direction);
	}
	return availableDirections;
}

void Ghost::exitGhostHouse()
{
	goToTarget(sf::Vector2i(11, 11));
}

void Ghost::updateStateTimer(float deltaTime)
{
	if (m_ghostState == GhostState::GlobalState) return;
	
	m_stateTimer -= deltaTime;
	if(m_stateTimer <= 0.f)
	{
		changeState(m_stateProperties[m_ghostState].nextState);
	}
}

void Ghost::restart()
{
	changeState(GhostState::GhostHouse);
	m_mapPosition = m_ghostHouse[0];
	setPosition(getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));
	setDirection(sf::Vector2i(0,1));
	goToTarget(m_ghostHouse[1]);
}
