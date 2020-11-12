#pragma once
#include "Ghost.h"
class Clyde :
	public Ghost
{
public:
	Clyde(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void beginPlay() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
};

