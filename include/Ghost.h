#pragma once
#include "Entity.h"
#include "Animation.h"

#include <array>

enum class GhostState
{
	Scatter,
	Chase,
	Frightened,
	GhostHouse,
	ExitGhostHouse,
	Eaten,
	GlobalState
};

struct GhostStateProperties
{
	GhostStateProperties() : duration(0.f), nextState(GhostState::GlobalState) {}
	GhostStateProperties(float dur, GhostState next) :
		duration(dur), nextState(next) {}
	float duration;
	GhostState nextState;
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

	void update(float deltaTime) override;
	void onCollision(Entity* otherEntity) override;

	sf::Vector2i getMapPosition() const;
	void changeGlobalState(GhostState newState);
	void changeState(GhostState newState);
	virtual void restart();
	
protected:
	void updateDirection();
	void findNextPosition();
	void setDirection(sf::Vector2i nextDirection);
	void changeAnimation();
	void goToTarget(sf::Vector2i position);
	bool checkPosition(sf::Vector2i position) const;
	virtual  void findChaseDirection() = 0;
	std::vector<sf::Vector2i> findAvailableDirections() const;
	void exitGhostHouse();
	void updateStateTimer(float deltaTime);
	
	GhostState m_ghostState;
	GhostState m_globalGhostState;
	std::unordered_map<GhostState, GhostStateProperties> m_stateProperties;
	float m_stateTimer;
	float m_ghostHouseTime;
	
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
	const float MOVEMENT_SPEED;
	const float FAST_MOVEMENT_SPEED;
	const float SLOW_MOVEMENT_SPEED;
};

class Blinky :
	public Ghost
{
public:
	Blinky(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
};

class Clyde :
	public Ghost
{
public:
	Clyde(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
};

class Inky :
	public Ghost
{
public:
	Inky(Game* game, const class PacMan* pacMan, const Ghost* blinky);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
	const Ghost* m_blinky;
};

class Pinky :
	public Ghost
{
public:
	Pinky(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
};