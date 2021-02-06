#include "Engine.h"
#include "Game.h"

Engine::Engine(Game* game) :
	m_game(game),
	sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(game->getWindowWidth()), static_cast<unsigned int>(game->getWindowHeight())), game->getTitle()),
	m_frameClock(),
	m_bShowFPS(false)
{
	
}

void Engine::start()
{
	m_resourceManager.loadFont("fps_font", "resources/fonts/fps_font.ttf");
	

	m_game->setEngine(this);
	m_game->launch();
	
	for(auto& entity : m_entities)
	{
		entity->beginPlay();
	}

	resetClock();
	
	while(isOpen())
	{
		sf::Event event;
		if(pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				close();
			}
		}
		
		const auto deltaTime = resetClock();

		m_game->update(deltaTime);
		updateEntities(deltaTime);
		checkEntitiesCollisions();
		checkForDestroyedEntities();
		
		clear();
		
		drawEntities();

		if (m_bShowFPS)
		{
			sf::Text fpsText(std::to_string(static_cast<int>(getFPS(deltaTime))), m_resourceManager.getFont("fps_font"));
			draw(fpsText);
		}
		
		display();
	}
}



float Engine::resetClock()
{
	return m_frameClock.restart().asSeconds();
}

float Engine::getFPS(float deltaTime) const
{
	return 1.f / deltaTime;
}

//Returns time between frames
float Engine::getDeltaTime() const
{
	return m_frameClock.getElapsedTime().asMilliseconds() / 1000.f;
}


void Engine::addEntity(Entity* entity)
{
	entity->setAlive();
	entity->loadResources(&m_resourceManager);
	entity->beginPlay();
	m_entities.push_back(entity);
}

void Engine::updateEntities(float deltaTime)
{
	for(auto& entity : m_entities)
	{
		if (entity->isAlive())
		{
			entity->update(deltaTime);
		}
	}
}

void Engine::drawEntities()
{
	for (auto& entity : m_entities)
	{
		if (entity->isAlive())
		{
			draw(*entity);
		}
	}
}

void Engine::checkEntitiesCollisions()
{
	for(auto movableEntity = m_entities.begin(); movableEntity != m_entities.end();++movableEntity)
	{
		if((*movableEntity)->isCollisionEnabled() && (*movableEntity)->isMovable())
		{
			for(auto otherEntity = m_entities.begin(); otherEntity != m_entities.end();++otherEntity)
			{
				if((*otherEntity)->isCollisionEnabled() && otherEntity != movableEntity)
				{
					if ((*otherEntity)->getCollisionRect().intersects((*movableEntity)->getCollisionRect()))
					{
						(*movableEntity)->onCollision(*otherEntity);
						(*otherEntity)->onCollision(*movableEntity);
					}
				}
			}
		}
	}
}

void Engine::checkForDestroyedEntities()
{
	for(auto it = m_entities.begin(); it != m_entities.end();)
	{
		if(!(*it)->isAlive())
		{
			it = m_entities.erase(it);
		}
		else
		{
			++it;
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
