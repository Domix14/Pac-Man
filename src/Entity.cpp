#include "Entity.h"

Entity::Entity(Game *game)
    : game(game), bDraw(true), bEnableCollision(false),
      bDrawCollisionRect(false), bMovable(false), sprite(),
      collisionRectOffset(), collisionRect(), bAlive(true) {}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (bDraw) {
    target.draw(sprite, states);
  }
}

const sf::Sprite &Entity::getSprite() const { return sprite; }

sf::Vector2f Entity::getPosition() const { return sprite.getPosition(); }

void Entity::setPosition(sf::Vector2f position) {
  sprite.setPosition(position);
  collisionRect.left = position.x + collisionRectOffset.x;
  collisionRect.top = position.y + collisionRectOffset.y;
}

bool Entity::isCollisionEnabled() const { return bEnableCollision; }

sf::FloatRect Entity::getCollisionRect() const { return collisionRect; }

bool Entity::isAlive() const { return bAlive; }

bool Entity::isMovable() const { return bMovable; }

void Entity::destroy() { bAlive = false; }

void Entity::setAlive() { bAlive = true; }

Game *Entity::getGame() const { return game; }
