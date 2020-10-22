#pragma once
#include "Entity.h"
class PacMan :
    public Entity
{
public:
	PacMan(class Game* game);
	
	virtual void loadResources(ResourceManager* resourceManager) override;
	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;
	
	void processInput();
	bool findDestination(sf::Vector2i direction);

protected:
	sf::Vector2i m_direction;
	sf::Vector2i m_mapPosition;
	sf::Vector2i m_nextDirection;
	sf::Vector2f m_destination;
	float m_movementSpeed;
};

