#include "Engine.h"


Engine::Engine(size_t width, size_t height, std::string title) :
	sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), title),
	m_frameClock(),
	m_bShowFPS(false)
{
}

void Engine::start()
{
	m_frameClock.restart();

	for(auto& entity : m_entities)
	{
		entity->beginPlay();
	}
	
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
		checkEntitiesCollisions();
		checkForDestroyedEntities();
		
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

void Engine::checkEntitiesCollisions()
{
	//TODO: Rename iterators
	for(auto it = m_entities.begin();it != m_entities.end();++it)
	{
		if((*it)->isCollisionEnabled())
		{
			for(auto it2 = (it + 1);it2 != m_entities.end();++it2)
			{
				if((*it2)->isCollisionEnabled())
				{
					if ((*it)->getCollisionRect().intersects((*it2)->getCollisionRect()))
					{
						(*it)->onCollision(*it2);
						(*it2)->onCollision(*it);
					}
				}
			}
		}
	}
}

void Engine::checkForDestroyedEntities()
{
	for(auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		if(!(*it)->isAlive())
		{
			it = m_entities.erase(it);
		}
	}
}

const ResourceManager* Engine::getResourceManager() const
{
	return &m_resourceManager;
}

void Engine::showFPS(bool bShow)
{
	m_bShowFPS = bShow;
}
