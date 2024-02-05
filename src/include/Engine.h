#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "ResourceManager.h"

class Game;

class Engine : public sf::RenderWindow {
public:
  Engine(Game *game);

  /*Starts the engine*/
  void start();

  /*Returns delta */
  float getDeltaTime() const;

  /*Add entity*/
  void addEntity(Entity *entity);

  /*Returns resource manager*/
  const ResourceManager *getResourceManager() const;

private:
  float resetClock();
  void updateEntities(float deltaTime);
  void drawEntities();
  void checkEntitiesCollisions();
  void checkForDestroyedEntities();

  Game *game;

  sf::Clock frameClock;

  std::vector<Entity *> entities;

  ResourceManager resourceManager;
};
