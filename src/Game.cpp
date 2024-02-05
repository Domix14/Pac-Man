#include "Game.h"

#include "Engine.h"

Game::Game(size_t width, size_t height, const std::string &title)
    : windowWidth(width), windowHeight(height), title(title) {}

size_t Game::getWindowWidth() const { return windowWidth; }

size_t Game::getWindowHeight() const { return windowHeight; }

std::string Game::getTitle() const { return title; }

void Game::setEngine(Engine *engine) { engine = engine; }

Engine *Game::getEngine() const { return engine; }
