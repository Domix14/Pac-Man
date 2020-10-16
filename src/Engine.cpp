#include "Engine.h"


Engine::Engine(size_t width, size_t height, std::string title) :
	sf::RenderWindow(sf::VideoMode(width, height), title),
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
	}
}

//Returns time between frames and restart clock
float Engine::getDeltaTime()
{
	return m_frameClock.restart().asSeconds();
}
