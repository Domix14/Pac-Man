#include "Level.h"

#include "Map.h"
#include "ResourceManager.h"

Level::Level(Game *game) : Entity(game) {
  sprite.setPosition(sf::Vector2f(0.f, BLOCK_WIDTH));
}

void Level::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("level", "resources/graphics/level.png");
  sprite.setTexture(resourceManager->getTexture("level"));
}
