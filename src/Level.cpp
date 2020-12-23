#include "Level.h"

#include "Map.h"
#include "ResourceManager.h"

Level::Level(Game* game) :
	Entity(game)
{
}

void Level::update(float deltaTime)
{
}

void Level::beginPlay()
{
	m_sprite.setPosition(sf::Vector2f(0.f, BLOCK_WIDTH));
}

void Level::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("level", "resources/graphics/level.png");
	m_sprite.setTexture(resourceManager->getTexture("level"));
}



void Level::onCollision(Entity* otherEntity)
{
	
}
