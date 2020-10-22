#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "ResourceManager.h"

class Engine :
    public sf::RenderWindow
{
public:
	Engine(size_t width, size_t height, std::string title);

	void start();
	float getDeltaTime() const;
	float resetClock();
	float getFPS(float deltaTime) const;
	
	void addEntity(Entity* entity);
	void updateEntities(float deltaTime);
	void drawEntities();
	void checkEntitiesCollisions();
	void checkForDestroyedEntities();
	const ResourceManager* getResourceManager() const;
	void showFPS(bool bShow);
	
	
private:
	sf::Clock m_frameClock;
	bool m_bShowFPS;
	
	std::vector<Entity*> m_entities;

	ResourceManager m_resourceManager;
};

