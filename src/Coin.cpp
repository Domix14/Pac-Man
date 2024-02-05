#include "Coin.h"

#include "ResourceManager.h"

Coin::Coin(Game *game) : Entity(game) {
  bEnableCollision = true;
  collisionRect.width = 10.f;
  collisionRect.height = 10.f;
  collisionRectOffset = {10.f, 10.f};
}

void Coin::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("coin", "resources/graphics/coin.png");
  sprite.setTexture(resourceManager->getTexture("coin"));
}
