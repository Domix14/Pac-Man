#include "PacManGame.h"

PacManGame::PacManGame() :
	Game(800, 600, "Pac-Man")
{
}

void PacManGame::launch()
{
	m_engine.start();
}
