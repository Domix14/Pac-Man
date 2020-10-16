#pragma once

#include <SFML/Graphics.hpp>

class Engine :
    public sf::RenderWindow
{
public:
	Engine(size_t width, size_t height, std::string title);

	void start();
	float getDeltaTime();

	
private:
	sf::Clock m_frameClock;
};

