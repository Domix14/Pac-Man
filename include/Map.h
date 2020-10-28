#pragma once

#include <SFML/System/Vector2.hpp>

constexpr  size_t WINDOW_WIDTH = 800;
constexpr size_t WINDOW_HEIGHT = 800;
constexpr float BLOCK_WIDTH = 40.f;

enum MapType
{
	Move = 0,
	Teleport = 1,
	GhostHouse = 2,
	Wall = 3
};

static sf::Vector2f getMapOffset()
{
	return sf::Vector2f{ 0.f, 0.f };
}

constexpr size_t getMapMaxRowIndex()
{
	return static_cast<size_t>(WINDOW_HEIGHT / 40.f) - 1;
}

constexpr size_t getMapMaxColumnIndex()
{
	return static_cast<size_t>(WINDOW_WIDTH / 40.f) - 1;
}

constexpr int map[getMapMaxColumnIndex() + 1][getMapMaxRowIndex() + 1] ={
								{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
								{3,1,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1,3},
								{3,0,3,0,3,0,3,3,3,3,3,0,3,0,3,3,3,3,0,3},
								{3,0,3,0,3,0,3,3,0,0,0,0,0,0,0,0,0,3,0,3},
								{3,0,3,0,0,0,3,3,0,3,3,3,3,0,3,3,0,3,0,3},
								{3,0,0,0,3,0,3,3,0,3,0,0,0,0,0,0,0,0,0,3},
								{3,0,3,0,3,0,0,0,0,0,0,3,0,3,0,3,3,3,0,3},
								{3,0,3,0,3,3,3,3,0,3,3,3,0,3,0,3,0,0,0,3},
								{3,0,3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,3,0,3},
								{3,0,0,0,0,0,0,3,3,3,0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,0,0,0,3,0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,0,3,0,0,0,0,0,3,0,3,0,0,0,3},
								{3,0,3,0,3,0,3,3,0,3,0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,0,0,0,3,0,3,0,3,0,3,0,3,0,3,0,3},
								{3,0,0,0,3,0,0,3,0,3,0,3,0,3,0,0,0,0,0,3},
								{3,0,3,0,3,0,0,0,0,0,0,0,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,3,3,3,3,3,3,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,0,0,0,0,2,2,2,2,3,3,3,3,0,3,0,3},
								{3,3,3,3,3,3,3,3,3,2,2,2,3,0,0,0,0,0,0,3},
								{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3} };
				