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
	float getDeltaTime();
	void addEntity(Entity* entity);
	void updateEntities(float deltaTime);
	void drawEntities();
	const ResourceManager* getResourceManager() const;
	
	
private:
	sf::Clock m_frameClock;
	
	std::vector<Entity*> m_entities;

	ResourceManager m_resourceManager;
};

