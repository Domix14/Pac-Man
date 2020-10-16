#include "Game.h"

Game::Game(size_t width, size_t height, const std::string& title) :
	m_engine(width, height, title)
{
}

void Game::launch()
{
	m_engine.start();
}

const Engine* Game::getEngine() const
{
	return &m_engine;
}
