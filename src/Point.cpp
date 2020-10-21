#include "Point.h"

#include "ResourceManager.h"

Point::Point(Game* game) :
	Entity(game)
{
}

void Point::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("point", "resources/graphics/point.png");
	m_sprite.setTexture(resourceManager->getTexture("point"));
}

void Point::update(float deltaTime)
{
}

void Point::beginPlay()
{
	m_bEnableCollision = true;
	m_bDrawCollisionRect = true;
	m_collisionRect.width = 20;
	m_collisionRect.height = 20;
}

void Point::onCollision(Entity* otherEntity)
{
	auto i = 10;
}
