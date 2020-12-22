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
	if (!Ghost::checkPosition(position)) return;

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
	m_movementSpeed(80.f),
	m_path()
{
	m_collisionRect.width = BLOCK_WIDTH;
	m_collisionRect.height = BLOCK_WIDTH;
	m_bEnableCollision = true;

	m_animation.addRects("right", { sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30) });
	m_animation.addRects("up", { sf::IntRect(0, 30, 30, 30), sf::IntRect(30, 30, 30, 30) });
	m_animation.addRects("left", { sf::IntRect(0, 60, 30, 30), sf::IntRect(30, 60, 30, 30) });
	m_animation.addRects("down", { sf::IntRect(0, 90, 30, 30), sf::IntRect(30, 90, 30, 30) });
	m_animation.setFrameTime(0.4f);
}

void Ghost::update(float deltaTime)
{
	m_animation.update(deltaTime, m_sprite);
	const sf::Vector2f nextPosition = getPosition() + (static_cast<sf::Vector2f>(m_direction) * m_movementSpeed * deltaTime);
	if (length(getPosition() - m_destination) > 2.f)
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
	findNextPosition();
}

void Ghost::onCollision(Entity* otherEntity)
{
	auto pacMan = dynamic_cast<PacMan*>(otherEntity);
	if(pacMan)
	{
		if(m_ghostState == GhostState::Frightened)
		{
			changeState(GhostState::Eaten);
		}
	}
}

void Ghost::changeState(GhostState newState)
{
	if (m_ghostState == newState) return;

	m_ghostState = newState;
	
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
}

void Ghost::findNextPosition()
{
	if (m_ghostState != GhostState::GhostHouse && map[m_mapPosition.y][m_mapPosition.x] == MapType::GhostHouse)
	{
		exitGhostHouse();
		return;
	}
	
	switch(m_ghostState)
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
				changeState(GhostState::Scatter);
			}
			break;
		}

		case GhostState::GhostHouse:
		{
			if (m_mapPosition != m_ghostHouse[0])
			{
				goToTarget(m_ghostHouse[0]);
			}
			else
			{
				m_path.mapPositions = m_ghostHouse;
				m_path.positionIndex = 0;
				updateDirection();
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

void Ghost::goToPosition(sf::Vector2i position)
{
	m_path.mapPositions.clear();
	m_path.positionIndex = 0;
	if(length(static_cast<sf::Vector2f>(m_mapPosition - position)) <= 1.0f)
	{
		m_path.addPosition(position);
		updateDirection();
	}
	else if(findRoute(std::vector<sf::Vector2i>{m_mapPosition}, m_path.mapPositions, position))
	{
		updateDirection();
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

bool Ghost::findRoute(std::vector<sf::Vector2i> path, std::vector<sf::Vector2i>& finalPath, const sf::Vector2i& destination)
{
	if (path.empty()) return false;

	auto addPath = [](sf::Vector2i pos, std::vector<sf::Vector2i> path) {path.push_back(pos); return path; };
	
	sf::Vector2i tilePosition = path.back() + sf::Vector2i(0, -1);
	if (checkPosition(tilePosition) && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}

	tilePosition = path.back() + sf::Vector2i(1, 0);
	if (checkPosition(tilePosition) && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}
	
	tilePosition = path.back() + sf::Vector2i(0, 1);
	if (checkPosition(tilePosition) && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}

	tilePosition = path.back() + sf::Vector2i(-1, 0);
	if (checkPosition(tilePosition) && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}
	
	return false;
}

bool Ghost::checkPosition(sf::Vector2i position)
{
	if (position.x < 0 ||
		position.y < 0 ||
		position.x > getMapMaxColumnIndex() ||
		position.y > getMapMaxRowIndex())
	{
		return false;
	}
	
	if(map[position.y][position.x] <= MapType::GhostHouse)
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
	if(availableDirections.empty())
	{
		availableDirections.push_back(-m_direction);
	}
	return availableDirections;
}

void Ghost::exitGhostHouse()
{
	goToTarget(sf::Vector2i(11, 11));
}

void Ghost::restart()
{
	m_mapPosition = START_POSITION;
	setPosition(getMapOffset() + sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));
	setDirection(START_DIRECTION);
}
