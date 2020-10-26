#include "Ghost.h"

#include "ResourceManager.h"
#include "Map.h"
#include "Utilities.h"

#include <algorithm>
#include <array>

sf::Vector2i Path::getNextMapPosition()
{
	//assert(!mapPositions.empty(), "Positions vector is empty!");
	const auto position = mapPositions[positionIndex];
	positionIndex = (++positionIndex) % mapPositions.size();
	return position;
}

Ghost::Ghost(Game* game) :
	Entity(game)
{
	
}

void Ghost::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("ghost", "resources/graphics/ghost.png");
	m_sprite.setTexture(resourceManager->getTexture("ghost"));
}

void Ghost::update(float deltaTime)
{

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
	m_collisionRect.width = BLOCK_WIDTH;
	m_collisionRect.height = BLOCK_WIDTH;
	m_movementSpeed = 80.f;

	m_mapPosition = sf::Vector2i(15, 1);
	setPosition(sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));


	m_scatterPath.emplace_back(18, 1);
	m_scatterPath.emplace_back(18, 2);
	m_scatterPath.emplace_back(18, 3);
	m_scatterPath.emplace_back(18, 4);
	m_scatterPath.emplace_back(18, 5);
	m_scatterPath.emplace_back(17, 5);
	m_scatterPath.emplace_back(16, 5);
	m_scatterPath.emplace_back(16, 4);
	m_scatterPath.emplace_back(16, 3);
	m_scatterPath.emplace_back(15, 3);
	m_scatterPath.emplace_back(14, 3);
	m_scatterPath.emplace_back(13, 3);
	m_scatterPath.emplace_back(13, 2);
	m_scatterPath.emplace_back(13, 1);
	m_scatterPath.emplace_back(14, 1);
	m_scatterPath.emplace_back(15, 1);
	m_scatterPath.emplace_back(16, 1);
	m_scatterPath.emplace_back(17, 1);
	changeState(GhostState::Frightened);
	
	m_bEnableCollision = true;
}

void Ghost::onCollision(Entity* otherEntity)
{
}

void Ghost::changeState(GhostState newState)
{
	if (m_ghostState == newState) return;

	m_ghostState = newState;
	findNextPosition();
}

void Ghost::updateDirection()
{
	const auto nextMapPosition = m_path.getNextMapPosition();
	m_direction = nextMapPosition - m_mapPosition;
	m_mapPosition = nextMapPosition;
	m_destination = sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH);
}

void Ghost::findNextPosition()
{
	switch(m_ghostState)
	{
		case GhostState::Scatter:
		{
			if (m_mapPosition != m_scatterPath[0])
			{
				goToPosition(m_scatterPath[0]);
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
			std::array<sf::Vector2i, 4> directions { sf::Vector2i{0,-1}, {1,0}, {0,1}, {-1,0} };
			std::vector<sf::Vector2i> avaibleDirections;
			avaibleDirections.reserve(3);
			for(const auto& direction : directions)
			{
				if(direction != m_direction && map[(m_mapPosition + direction).y][(m_mapPosition + direction).x] == 0)
				{
					avaibleDirections.push_back(direction);
				}
			}

			const int index = randRange(0, avaibleDirections.size() - 1);
			goToPosition(m_mapPosition + avaibleDirections[index]);
		}
	}
}

void Ghost::goToPosition(sf::Vector2i position)
{
	m_path.mapPositions.clear();
	if(findRoute(std::vector<sf::Vector2i>{m_mapPosition}, m_path.mapPositions, position))
	{
		updateDirection();
	}
}

bool Ghost::findRoute(std::vector<sf::Vector2i> path, std::vector<sf::Vector2i>& finalPath, const sf::Vector2i& destination)
{
	if (path.empty()) return false;
	//TODO: Implement index range checking

	auto addPath = [](sf::Vector2i pos, std::vector<sf::Vector2i> path) {path.push_back(pos); return path; };
	
	sf::Vector2i tilePosition = path.back() + sf::Vector2i(0, -1);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}

	tilePosition = path.back() + sf::Vector2i(1, 0);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}
	
	tilePosition = path.back() + sf::Vector2i(0, 1);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}

	tilePosition = path.back() + sf::Vector2i(-1, 0);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.insert(finalPath.begin(), tilePosition);
			return true;
		}
	}
	
	return false;
}
