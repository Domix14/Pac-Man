#include "PacManGame.h"

#include "Map.h"

PacManGame::PacManGame() :
	Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man"),
	m_pacMan(this),
	m_ghost(this),
	m_level(this)
{
}

void PacManGame::launch()
{
	m_engine.addEntity(&m_pacMan);
	m_engine.addEntity(&m_ghost);

	m_engine.addEntity(&m_level);
	spawnPoints();

	//m_engine.showFPS(true);

	//m_engine.setFramerateLimit(144);
	m_engine.start();
}

void PacManGame::spawnPoints()
{
	m_points.reserve(40);
	for(size_t x = 0;x < getMapMaxColumnIndex();x++)
	{
		for(size_t y = 0;y < getMapMaxRowIndex();y++)
		{
			if(map[y][x] == MapType::Move)
			{
				m_points.emplace_back(this);
				m_points.back().setPosition(getMapOffset() + sf::Vector2f(x * BLOCK_WIDTH + 10.f, y * BLOCK_WIDTH + 10.f));
			}
		}
	}

	for(auto& point : m_points)
	{
		m_engine.addEntity(&point);
	}
}
