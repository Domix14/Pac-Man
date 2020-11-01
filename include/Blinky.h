#pragma once
#include "Ghost.h"
class Blinky :
	public Ghost
{
public:
	Blinky(class Game* game, const class PacMan* pacMan);

	sf::Vector2i findChaseDirection() override;
	void beginPlay() override;
	
private:
	const class PacMan* m_pacMan;
};

