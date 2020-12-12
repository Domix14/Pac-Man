#include "Coin.h"

#include "ResourceManager.h"

Coin::Coin(Game* game) :
	Entity(game)
{
	m_bEnableCollision = true;
	m_bDrawCollisionRect = true;
	m_collisionRect.width = 10;
	m_collisionRect.height = 10;
}

void Coin::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("coin", "resources/graphics/coin.png");
	m_sprite.setTexture(resourceManager->getTexture("coin"));
}

void Coin::update(float deltaTime)
{
}

void Coin::beginPlay()
{
}

void Coin::onCollision(Entity* otherEntity)
{
}