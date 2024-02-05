#include "PowerUp.h"
#include "ResourceManager.h"

PowerUp::PowerUp(Game *game) : Entity(game) {
  bEnableCollision = true;
  collisionRect.width = 10;
  collisionRect.height = 10;
  collisionRectOffset = {10.f, 10.f};
}

void PowerUp::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("power_up", "resources/graphics/power_up.png");
  sprite.setTexture(resourceManager->getTexture("power_up"));
}