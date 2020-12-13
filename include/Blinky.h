#pragma once
#include "Ghost.h"
class Blinky :
	public Ghost
{
public:
	Blinky(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;
	
private:
	const class PacMan* m_pacMan;
};

