#include "Level.h"

#include "Map.h"

Level::Level(Game* game) :
	Entity(game)
{
}

void Level::update(float deltaTime)
{
}

void Level::beginPlay()
{
	sf::RectangleShape block(sf::Vector2f(BLOCK_WIDTH, BLOCK_WIDTH));
	block.setFillColor(sf::Color::Blue);

	for(size_t x = 0;x < 20;x++)
	{
		for(size_t y = 0;y < 20;y++)
		{
			if(map[y][x] == 1)
			{
				block.setPosition(sf::Vector2f(x * BLOCK_WIDTH, y * BLOCK_WIDTH));
				m_blocks.push_back(block);
			}
		}
	}
}

void Level::loadResources(ResourceManager* resourceManager)
{
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& block : m_blocks)
	{
		target.draw(block, states);
	}
}

void Level::onCollision(Entity* otherEntity)
{
	
}
