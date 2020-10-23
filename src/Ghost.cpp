#include "Ghost.h"

#include "ResourceManager.h"
#include "Map.h"
#include "Utilities.h"

#include <algorithm>

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
		if (!m_path.empty())
		{
			m_direction = m_path.top() - m_mapPosition;
			m_mapPosition = m_path.top();
			m_destination = sf::Vector2f(m_path.top().x * BLOCK_WIDTH, m_path.top().y * BLOCK_WIDTH);
			m_path.pop();
		}
	}
	
}

void Ghost::beginPlay()
{
	m_collisionRect.width = BLOCK_WIDTH;
	m_collisionRect.height = BLOCK_WIDTH;
	m_movementSpeed = 80.f;

	m_mapPosition = sf::Vector2i(1, 15);
	setPosition(sf::Vector2f(m_mapPosition.x * BLOCK_WIDTH, m_mapPosition.y * BLOCK_WIDTH));

	goToPosition(sf::Vector2i(3, 1));
	
	m_bEnableCollision = true;
}

void Ghost::onCollision(Entity* otherEntity)
{
}

void Ghost::goToPosition(sf::Vector2i position)
{
	while(!m_path.empty())
	{
		m_path.pop();
	}

	if (findRoute(std::vector<sf::Vector2i> {m_mapPosition}, m_path, position))
	{
		m_direction = m_path.top() - m_mapPosition;
		m_mapPosition = m_path.top();
		m_destination = sf::Vector2f(m_path.top().x * BLOCK_WIDTH, m_path.top().y * BLOCK_WIDTH);
		m_path.pop();
	}
}

bool Ghost::findRoute(std::vector<sf::Vector2i> path, std::stack<sf::Vector2i>& finalPath, const sf::Vector2i& destination)
{
	if (path.empty()) return false;
	//TODO: Implement index range checking

	auto addPath = [](sf::Vector2i pos, std::vector<sf::Vector2i> path) {path.push_back(pos); return path; };
	
	sf::Vector2i tilePosition = path.back() + sf::Vector2i(0, -1);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.push(tilePosition);
			return true;
		}
	}

	tilePosition = path.back() + sf::Vector2i(1, 0);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination || findRoute(addPath(tilePosition, path), finalPath, destination))
		{
			finalPath.push(tilePosition);
			return true;
		}
	}
	
	/*tilePosition = path.back() + sf::Vector2i(1, 0);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination)
		{
			finalPath.push_back(tilePosition);
			return true;
		}
		else
		{
			return findRoute(path, finalPath, destination);
		}
	}

	tilePosition = path.back() + sf::Vector2i(0, 1);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination)
		{
			finalPath.push_back(tilePosition);
			return true;
		}
		else
		{
			return findRoute(path, finalPath, destination);
		}
	}

	tilePosition = path.back() + sf::Vector2i(-1, 0);
	if (map[tilePosition.y][tilePosition.x] == 0 && std::find(path.begin(), path.end(), tilePosition) == path.end())
	{
		if (tilePosition == destination)
		{
			finalPath.push_back(tilePosition);
			return true;
		}
		else
		{
			return findRoute(path, finalPath, destination);
		}
	}*/

	
	return false;
}
