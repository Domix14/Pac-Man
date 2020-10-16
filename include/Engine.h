#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

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
	
private:
	sf::Clock m_frameClock;
	std::vector<Entity*> m_entities;
};

