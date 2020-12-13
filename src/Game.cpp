#include "Game.h"

Game::Game(size_t width, size_t height, const std::string& title) :
	m_engine(width, height, title)
{
}

void Game::launch()
{
	m_engine.start();
}

void Game::update(float deltaTime)
{
}

const Engine* Game::getEngine() const
{
	return &m_engine;
}
