#pragma once
#include "Animation.h"
#include "Entity.h"

class PacMan : public Entity {
public:
  PacMan(class Game *game);

  void loadResources(ResourceManager *resourceManager) override;
  void update(float deltaTime) override;
  void onCollision(Entity *otherEntity) override;

  void beginPlay() override{};

  /*Restart PacMan position*/
  void restart();

  /*Returns map position*/
  sf::Vector2i getMapPosition() const;

  /*Returns direction*/
  sf::Vector2i getDirection() const;

private:
  void updatePosition(float deltaTime);
  void changeAnimation();
  void processInput();
  void setDirection(sf::Vector2i newDirection);
  bool findDestination(sf::Vector2i direction);

  const sf::Vector2i START_POSITION;
  const sf::Vector2i START_DIRECTION;

  Animation animation;

  sf::Vector2i direction;
  sf::Vector2i mapPosition;
  sf::Vector2i nextDirection;
  sf::Vector2f destination;
  float movementSpeed;
};
