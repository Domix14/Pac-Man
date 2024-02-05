#pragma once

#include <SFML/Graphics.hpp>

class Game;

enum CollisionChannel {
  Player = 1,
  Enemy = 2,
  World = 3,
};

class Entity : public sf::Drawable {
public:
  Entity(Game *game);
  virtual ~Entity() = default;

  /*Draw function, called every frame to draw sprite, can be overriden*/
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  /*Called when added to engine*/
  virtual void beginPlay() = 0;

  /*Called every frame*/
  virtual void update(float deltaTime) = 0;

  /*Called when added to engine*/
  virtual void loadResources(class ResourceManager *resourceManager) = 0;

  /*Called when collision is detected*/
  virtual void onCollision(Entity *otherEntity) = 0;

  /*Returns sprite*/
  const sf::Sprite &getSprite() const;

  /*Returns position*/
  sf::Vector2f getPosition() const;

  /*Return true if collision is enabled*/
  bool isCollisionEnabled() const;

  /*Return collision rect*/
  sf::FloatRect getCollisionRect() const;

  /*Returns true if Entity can move*/
  bool isMovable() const;

  /*Set new position of entity*/
  void setPosition(sf::Vector2f position);

  /*Returns true if Entity is alive*/
  bool isAlive() const;

  /*Set Entity to alive state*/
  void setAlive();

  /*Destroy the Entity*/
  void destroy();

protected:
  Game *getGame() const;

  Game *const game;

  bool bDraw;
  bool bEnableCollision;
  bool bDrawCollisionRect;
  bool bMovable;

  sf::Sprite sprite;
  sf::Vector2f collisionRectOffset;
  sf::FloatRect collisionRect;

private:
  bool bAlive;
};
