#pragma once
#include "Entity.h"

#include <stack>

enum class GhostState
{
	Scatter,
	Chase,
	Frightened,
	Eaten
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

	void goToPosition(sf::Vector2i position);
	bool findRoute(std::vector<sf::Vector2i> path, std::stack<sf::Vector2i>& finalPath, const sf::Vector2i& destination);
	
private:
	std::stack<sf::Vector2i> m_path;
	
	sf::Vector2i m_direction;
	sf::Vector2i m_mapPosition;
	sf::Vector2f m_destination;
	float m_movementSpeed;
};

