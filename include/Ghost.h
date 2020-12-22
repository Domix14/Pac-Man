#pragma once
#include "Entity.h"
#include "Animation.h"

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
	void addPosition(sf::Vector2i position);
};

class Ghost :
    public Entity
{
public:
	Ghost(Game* game);

	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;

	void changeState(GhostState newState);
	sf::Vector2i getMapPosition() const;
	void updateDirection();
	void findNextPosition();
	void setDirection(sf::Vector2i nextDirection);
	void changeAnimation();
	void goToPosition(sf::Vector2i position);
	void goToTarget(sf::Vector2i position);
	bool findRoute(std::vector<sf::Vector2i> path, std::vector<sf::Vector2i>& finalPath, const sf::Vector2i& destination);
	static bool checkPosition(sf::Vector2i position);
	virtual  void findChaseDirection() = 0;
	std::vector<sf::Vector2i> findAvailableDirections() const;
	void exitGhostHouse();
	void restart();

	
protected:
	GhostState m_ghostState;

	std::array<sf::Vector2i, 2> teleportPositions{ sf::Vector2i{1,1}, {18,1} };
	
	Path m_path;
	std::vector<sf::Vector2i> m_scatterPath;
	std::vector<sf::Vector2i> m_ghostHouse;

	const sf::Vector2i START_POSITION;
	const sf::Vector2i START_DIRECTION;
	
	Animation m_animation;

	sf::Vector2i m_direction;
	sf::Vector2i m_mapPosition;
	sf::Vector2f m_destination;
	float m_movementSpeed;
};

