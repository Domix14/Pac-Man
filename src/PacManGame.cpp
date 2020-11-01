#include "PacManGame.h"

#include "Map.h"
#include "Utilities.h"

PacManGame::PacManGame() :
	Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man"),
	m_pacMan(this),
	m_blinky(this, &m_pacMan),
	m_level(this),
	m_scoreText(this),
	m_score(0)
{
}

void PacManGame::launch()
{
	m_engine.addEntity(&m_scoreText);
	m_engine.addEntity(&m_pacMan);
	m_engine.addEntity(&m_blinky);

	m_engine.addEntity(&m_level);
	spawnCoins();

	//m_engine.showFPS(true);

	//m_engine.setFramerateLimit(144);
	m_engine.start();
}

void PacManGame::spawnCoins()
{
	m_coins.reserve(40);
	for(size_t x = 0;x < getMapMaxColumnIndex();x++)
	{
		for(size_t y = 0;y < getMapMaxRowIndex();y++)
		{
			if(map[y][x] == MapType::Move)
			{
				m_coins.emplace_back(this);
				m_coins.back().setPosition(getMapOffset() + sf::Vector2f(x * BLOCK_WIDTH + 5.f, y * BLOCK_WIDTH + 5.f));
			}
		}
	}

	for(auto& point : m_coins)
	{
		m_engine.addEntity(&point);
	}
}

void PacManGame::addScore(size_t score)
{
	m_score += score;
	m_scoreText.updateScore(m_score);
}

void PacManGame::killPacMan()
{
	m_lives--;
	if(m_lives < 0)
	{
		//TODO: Restart whole game
	}
	else
	{
		restartPositions();
	}
}

void PacManGame::restartPositions()
{
	m_pacMan.restart();
	m_blinky.restart();
}
