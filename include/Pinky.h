#pragma once
#include "Ghost.h"
class Pinky :
	public Ghost
{
public:
	Pinky(class Game* game, const class PacMan* pacMan);

	void findChaseDirection() override;
	void loadResources(ResourceManager* resourceManager) override;

private:
	const class PacMan* m_pacMan;
};

