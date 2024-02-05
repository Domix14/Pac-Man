#include "Engine.h"
#include "Game.h"

Engine::Engine(Game *game)
    : sf::RenderWindow(
          sf::VideoMode(static_cast<unsigned int>(game->getWindowWidth()),
                        static_cast<unsigned int>(game->getWindowHeight())),
          game->getTitle()),
      game(game), frameClock(), entities(), resourceManager() {}

void Engine::start() {
  resourceManager.loadFont("fps_font", "resources/fonts/fps_font.ttf");

  game->setEngine(this);
  game->launch();

  for (auto &entity : entities) {
    entity->beginPlay();
  }

  resetClock();

  while (isOpen()) {
    sf::Event event;
    if (pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        close();
      }
    }

    const auto deltaTime = resetClock();

    game->update(deltaTime);
    updateEntities(deltaTime);
    checkEntitiesCollisions();
    checkForDestroyedEntities();

    clear();

    drawEntities();

    display();
  }
}

float Engine::resetClock() { return frameClock.restart().asSeconds(); }

// Returns time between frames
float Engine::getDeltaTime() const {
  return frameClock.getElapsedTime().asMilliseconds() / 1000.f;
}

void Engine::addEntity(Entity *entity) {
  entity->setAlive();
  entity->loadResources(&resourceManager);
  entity->beginPlay();
  entities.push_back(entity);
}

void Engine::updateEntities(float deltaTime) {
  for (auto &entity : entities) {
    if (entity->isAlive()) {
      entity->update(deltaTime);
    }
  }
}

void Engine::drawEntities() {
  for (auto &entity : entities) {
    if (entity->isAlive()) {
      draw(*entity);
    }
  }
}

void Engine::checkEntitiesCollisions() {
  for (auto movableEntity = entities.begin(); movableEntity != entities.end();
       ++movableEntity) {
    if ((*movableEntity)->isCollisionEnabled() &&
        (*movableEntity)->isMovable()) {
      for (auto otherEntity = entities.begin(); otherEntity != entities.end();
           ++otherEntity) {
        if ((*otherEntity)->isCollisionEnabled() &&
            otherEntity != movableEntity) {
          if ((*otherEntity)
                  ->getCollisionRect()
                  .intersects((*movableEntity)->getCollisionRect())) {
            (*movableEntity)->onCollision(*otherEntity);
            (*otherEntity)->onCollision(*movableEntity);
          }
        }
      }
    }
  }
}

void Engine::checkForDestroyedEntities() {
  for (auto it = entities.begin(); it != entities.end();) {
    if (!(*it)->isAlive()) {
      it = entities.erase(it);
    } else {
      ++it;
    }
  }
}

const ResourceManager *Engine::getResourceManager() const {
  return &resourceManager;
}
