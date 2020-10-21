#pragma once

constexpr  size_t WINDOW_WIDTH = 800;
constexpr size_t WINDOW_HEIGHT = 800;
constexpr float BLOCK_WIDTH = 40.f;

constexpr size_t getMapMaxRowIndex()
{
	return static_cast<size_t>(WINDOW_HEIGHT / 40.f) - 1;
}

constexpr size_t getMapMaxColumnIndex()
{
	return static_cast<size_t>(WINDOW_WIDTH / 40.f) - 1;
}

constexpr int map[getMapMaxColumnIndex() + 1][getMapMaxRowIndex() + 1] ={
								{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
								{1,0,1,0,1,1,0,0,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,1,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1},
								{1,0,1,0,0,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,1},
								{1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1},
								{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
				