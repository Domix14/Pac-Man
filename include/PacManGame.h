#pragma once

#include "Game.h"

#include "PacMan.h"
#include "Coin.h"
#include "Level.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "ScoreText.h"
#include "PowerUp.h"

class PacManGame : public Game
{
public:
	PacManGame();
	virtual void launch() override;

	void spawnCoins();
	void addScore(size_t score);
	void killPacMan();
	void restartPositions();
protected:
	PacMan m_pacMan;
	Blinky m_blinky;
	Clyde m_clyde;
	Pinky m_pinky;
	Inky m_inky;
	std::vector<Coin> m_coins;
	std::vector<PowerUp> m_Powers;
	Level m_level;
	ScoreText m_scoreText;
	
	size_t m_score;
	int m_lives;
};

