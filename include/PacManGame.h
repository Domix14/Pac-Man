#pragma once

#include "Game.h"

#include "PacMan.h"
#include "Level.h"

class PacManGame : public Game
{
public:
	PacManGame();
	virtual void launch() override;

protected:
	PacMan m_pacMan;
	Level m_level;
};

