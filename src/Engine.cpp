#include "Engine.h"


Engine::Engine(size_t width, size_t height, std::string title) :
	sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), title),
	m_frameClock()
{
}

void Engine::start()
{
	m_frameClock.restart();
	
	while(isOpen())
	{
		//TODO: Rework?
		sf::Event event;
		if(pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				close();
			}
		}
		
		const auto deltaTime = getDeltaTime();

		updateEntities(deltaTime);
		
		clear();
		drawEntities();
		display();
	}
}

//Returns time between frames and restart clock
float Engine::getDeltaTime()
{
	return m_frameClock.restart().asSeconds();
}

void Engine::addEntity(Entity* entity)
{
	entity->loadResources(&m_resourceManager);
	m_entities.push_back(entity);
}

void Engine::updateEntities(float deltaTime)
{
	for(auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void Engine::drawEntities()
{
	for (auto& entity : m_entities)
	{
		draw(*entity);
	}
}

const ResourceManager* Engine::getResourceManager() const
{
	return &m_resourceManager;
}
