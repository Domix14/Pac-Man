#include "PacManGame.h"

#include "Map.h"

PacManGame::PacManGame() :
	Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man"),
	m_pacMan(this),
	m_level(this)
{
}

void PacManGame::launch()
{
	m_pacMan.setPosition({ 100.f, 100.f });
	m_engine.addEntity(&m_pacMan);

	m_engine.addEntity(&m_level);
	
	m_engine.start();
}
