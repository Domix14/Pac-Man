#include "PacManGame.h"

#include "Map.h"
#include "Utilities.h"

#include "Engine.h"

PacManGame::PacManGame() :
	Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man"),
	m_currentLevel(0),
	m_pacMan(this),
	m_blinky(this, &m_pacMan),
	m_pinky(this, &m_pacMan),
	m_clyde(this, &m_pacMan),
	m_inky(this, &m_pacMan, &m_blinky),
	m_level(this),
	m_scoreText(this),
	m_score(0)
{
	m_statesProperties[NewGame].emplace_back(2.f, 0, 1, GameState::Scatter, GhostState::GhostHouse);
	m_statesProperties[Scatter].emplace_back(10.f, 0, 1, GameState::Chase, GhostState::Scatter);
	m_statesProperties[Chase].emplace_back(10.f, 0, 1, GameState::Scatter, GhostState::Chase);
}

PacManGame::~PacManGame()
{
	
}

void PacManGame::launch()
{
	getEngine()->addEntity(&m_scoreText);
	getEngine()->addEntity(&m_pacMan);
	getEngine()->addEntity(&m_blinky);
	getEngine()->addEntity(&m_pinky);
	getEngine()->addEntity(&m_clyde);
	getEngine()->addEntity(&m_inky);

	getEngine()->addEntity(&m_level);
	spawnCoins();

	restartGame();
}

void PacManGame::update(float deltaTime)
{
	updateState(deltaTime);
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
			else if(map[y][x] == MapType::PowerUpPosition)
			{
				m_Powers.emplace_back(this);
				m_Powers.back().setPosition(getMapOffset() + sf::Vector2f(x * BLOCK_WIDTH + 5.f, y * BLOCK_WIDTH + 5.f));
			}
		}
	}

	for(auto& coin : m_coins)
	{
		getEngine()->addEntity(&coin);
	}
	for (auto& Power : m_Powers)
	{
		getEngine()->addEntity(&Power);
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
	m_pinky.restart();
	m_inky.restart();
	m_clyde.restart();
}

void PacManGame::restartGame()
{
	restartPositions();
	changeState(GameState::NewGame);
}

void PacManGame::changeState(GameState state)
{
	auto& properties = m_statesProperties[state];
	for(auto& p : properties)
	{
		if(p.firstLevel <= m_currentLevel && p.lastLevel >= m_currentLevel)
		{
			m_state = state;
			m_stateTimer = p.duration;
			m_blinky.changeState(p.ghostState);
			m_pinky.changeState(p.ghostState);
			m_inky.changeState(p.ghostState);
			m_clyde.changeState(p.ghostState);
		}
	}
}

void PacManGame::updateState(float deltaTime)
{
	m_stateTimer -= deltaTime;
	if(m_stateTimer <= 0.f)
	{
		auto& properties = m_statesProperties[m_state];
		for (auto& p : properties)
		{
			if (p.firstLevel <= m_currentLevel && p.lastLevel >= m_currentLevel)
			{
				changeState(p.nextState);
			}
		}
	}
}
