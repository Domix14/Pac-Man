#include "PowerUp.h"
#include "ResourceManager.h"

PowerUp::PowerUp(Game* game) :
	Entity(game)
{
	m_bEnableCollision = true;
	m_bDrawCollisionRect = true;
	m_collisionRect.width = 10;
	m_collisionRect.height = 10;
}

void PowerUp::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadTexture("power_up", "resources/graphics/power_up.png");
	m_sprite.setTexture(resourceManager->getTexture("power_up"));
}

void PowerUp::update(float deltaTime)
{
}

void PowerUp::beginPlay()
{
}

void PowerUp::onCollision(Entity* otherEntity)
{
}