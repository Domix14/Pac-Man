#pragma once

#include <SFML/System/Vector2.hpp>

constexpr  size_t WINDOW_WIDTH = 630;
constexpr size_t WINDOW_HEIGHT = 840;

constexpr  size_t MAP_WIDTH = 690;
constexpr size_t MAP_HEIGHT = 810;
constexpr float BLOCK_WIDTH = 30.f;

enum MapType
{
	Move = 0,
	PowerUpPosition = 1,
	Teleport = 2,
	GhostHouse = 3,
	Wall = 4
};

static sf::Vector2f getMapOffset()
{
	return sf::Vector2f{ -BLOCK_WIDTH, BLOCK_WIDTH };
}

constexpr size_t getMapMaxRowIndex()
{
	return static_cast<size_t>(MAP_HEIGHT / BLOCK_WIDTH) - 1;
}

constexpr size_t getMapMaxColumnIndex()
{
	return static_cast<size_t>(MAP_WIDTH / BLOCK_WIDTH) - 1;
}

constexpr int map[getMapMaxRowIndex() + 1][getMapMaxColumnIndex() + 1] ={
								{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
								{4,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4},
								{4,4,0,4,4,4,0,4,4,4,0,4,0,4,4,4,0,4,4,4,0,4,4},
								{4,4,1,4,4,4,0,4,4,4,0,4,0,4,4,4,0,4,4,4,1,4,4},
								{4,4,0,4,4,4,0,4,4,4,0,4,0,4,4,4,0,4,4,4,0,4,4},
								{4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4},
								{4,4,0,4,4,4,0,4,0,4,4,4,4,4,0,4,0,4,4,4,0,4,4},
								{4,4,0,4,4,4,0,4,0,4,4,4,4,4,0,4,0,4,4,4,0,4,4},
								{4,4,0,0,0,0,0,4,0,0,0,4,0,0,0,4,0,0,0,0,0,4,4},
								{4,4,4,4,4,4,0,4,4,4,0,4,0,4,4,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,0,0,0,0,0,0,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,4,4,3,4,4,0,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,4,3,3,3,4,0,4,0,4,4,4,4,4,4},
								{2,0,0,0,0,0,0,0,0,4,3,3,3,4,0,0,0,0,0,0,0,0,2},
								{4,4,4,4,4,4,0,4,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,0,0,0,0,0,0,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4},
								{4,4,4,4,4,4,0,4,0,4,4,4,4,4,0,4,0,4,4,4,4,4,4},
								{4,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,4},
								{4,4,0,4,4,4,0,4,4,4,0,4,0,4,4,4,0,4,4,4,0,4,4},
								{4,4,1,0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,1,4,4},
								{4,4,4,4,0,4,0,4,0,4,4,4,4,4,0,4,0,4,0,4,4,4,4},
								{4,4,4,4,0,4,0,4,0,4,4,4,4,4,0,4,0,4,0,4,4,4,4},
								{4,4,0,0,0,0,0,4,0,0,0,4,0,0,0,4,0,0,0,0,0,4,4},
								{4,4,0,4,4,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4,0,4,4},
								{4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4},
								{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}};
				