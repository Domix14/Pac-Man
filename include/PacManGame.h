#pragma once

#include "Game.h"

#include "PacMan.h"
#include "Point.h"
#include "Level.h"
#include "Ghost.h"

class PacManGame : public Game
{
public:
	PacManGame();
	virtual void launch() override;

	void spawnPoints();
protected:
	PacMan m_pacMan;
	Ghost m_ghost;
	std::vector<Point> m_points;
	Level m_level;
};

