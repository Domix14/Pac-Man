#pragma once

#include "Game.h"

#include "PacMan.h"
#include "Coin.h"
#include "Level.h"
#include "Ghost.h"
#include "ScoreText.h"

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
	Ghost m_ghost;
	std::vector<Coin> m_coins;
	Level m_level;
	ScoreText m_scoreText;
	
	size_t m_score;
	int m_lives;
};

