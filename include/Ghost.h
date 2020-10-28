#pragma once
#include "Entity.h"

#include <stack>
#include <array>

enum class GhostState
{
	Scatter,
	Chase,
	Frightened,
	GhostHouse,
	Eaten
};

struct Path
{
	Path() :
	positionIndex(0) {}
	
	std::vector<sf::Vector2i> mapPositions;
	size_t positionIndex;

	sf::Vector2i getNextMapPosition();
};

class Ghost :
    public Entity
{
public:
	Ghost(Game* game);

	virtual void loadResources(ResourceManager* resourceManager) override;
	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;

	void changeState(GhostState newState);
	void updateDirection();
	void findNextPosition();
	void goToPosition(sf::Vector2i position);
	bool findRoute(std::vector<sf::Vector2i> path, std::vector<sf::Vector2i>& finalPath, const sf::Vector2i& destination);
	bool checkPosition(sf::Vector2i position) const;
	void setPosition(sf::Vector2f newPosition);
	
private:
	GhostState m_ghostState;

	std::array<sf::Vector2i, 2> teleportPositions{ sf::Vector2i{1,1}, {18,1} };
	
	Path m_path;
	std::vector<sf::Vector2i> m_scatterPath;
	std::vector<sf::Vector2i> m_ghostHouse;
	//std::stack<sf::Vector2i> m_path;

	
	sf::Vector2i m_direction;
	sf::Vector2i m_mapPosition;
	sf::Vector2f m_destination;
	float m_movementSpeed;
};

