#include "PacMan.h"

#include "Coin.h"
#include "Map.h"
#include "PacManGame.h"
#include "ResourceManager.h"


#include "Utilities.h"

PacMan::PacMan(Game *game)
    : Entity(game), START_POSITION({11, 20}), START_DIRECTION({0, -1}),
      movementSpeed(100.f) {
  bMovable = true;
  bEnableCollision = true;
  collisionRect.width = 15;
  collisionRect.height = 15;
  collisionRectOffset = {7.5f, 7.5f};
}

void PacMan::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("pacman_anim",
                               "resources/graphics/pacman_anim.png");
  sprite.setTexture(resourceManager->getTexture("pacman_anim"));

  animation.addRects("right",
                     {sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30)});
  animation.addRects("up",
                     {sf::IntRect(0, 30, 30, 30), sf::IntRect(30, 30, 30, 30)});
  animation.addRects("left",
                     {sf::IntRect(0, 60, 30, 30), sf::IntRect(30, 60, 30, 30)});
  animation.addRects("down",
                     {sf::IntRect(0, 90, 30, 30), sf::IntRect(30, 90, 30, 30)});
  animation.setFrameTime(0.25f);
  animation.setAnimation("down", sprite);
}

void PacMan::update(float deltaTime) {
  processInput();
  animation.update(deltaTime, sprite);

  updatePosition(deltaTime);
}

void PacMan::updatePosition(float deltaTime) {
  // Allows to turn back in any moment
  const auto directionDiff = direction + nextDirection;
  if (directionDiff.x == 0 && directionDiff.y == 0) {
    if (findDestination(nextDirection)) {
      setDirection(nextDirection);
    }
  }

  // Calculate next position
  const sf::Vector2f nextPosition =
      getPosition() +
      (static_cast<sf::Vector2f>(direction) * movementSpeed * deltaTime);

  // Prevent to move more than one block in one frame
  if (length(nextPosition - destination) <
      length(getPosition() - destination)) {
    setPosition(nextPosition);
  } else {
    setPosition(destination);
    if (findDestination(nextDirection)) {
      setDirection(nextDirection);
    } else {
      findDestination(direction);
    }
  }
}

void PacMan::onCollision(Entity *otherEntity) {
  auto *point = dynamic_cast<Coin *>(otherEntity);
  if (point) {
    auto *game = dynamic_cast<PacManGame *>(getGame());
    if (game) {
      point->destroy();
      game->pickCoin();
    }
  } else {
    auto *powerUp = dynamic_cast<PowerUp *>(otherEntity);
    if (powerUp) {
      auto *game = dynamic_cast<PacManGame *>(getGame());
      if (game) {
        powerUp->destroy();
        game->pickPowerUp();
      }
    }
  }
}

void PacMan::changeAnimation() {
  if (direction == sf::Vector2i(0, -1)) {
    animation.setAnimation("up", sprite);
  } else if (direction == sf::Vector2i(1, 0)) {
    animation.setAnimation("right", sprite);
  } else if (direction == sf::Vector2i(0, 1)) {
    animation.setAnimation("down", sprite);
  } else if (direction == sf::Vector2i(-1, 0)) {
    animation.setAnimation("left", sprite);
  }
}

void PacMan::processInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
      nextDirection != sf::Vector2i(0, -1)) {
    nextDirection = sf::Vector2i(0, -1);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
             nextDirection != sf::Vector2i(1, 0)) {
    nextDirection = sf::Vector2i(1, 0);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
             nextDirection != sf::Vector2i(0, 1)) {
    nextDirection = sf::Vector2i(0, 1);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
             nextDirection != sf::Vector2i(-1, 0)) {
    nextDirection = sf::Vector2i(-1, 0);
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    auto *game = dynamic_cast<PacManGame *>(getGame());
    if (game) {
      game->openMenu();
      game->closeGame();
    }
  }
}

void PacMan::setDirection(sf::Vector2i newDirection) {
  direction = newDirection;
  changeAnimation();
}

bool PacMan::findDestination(sf::Vector2i direction) {
  if (map[mapPosition.y][mapPosition.x] == MapType::Teleport) {
    mapPosition -= sf::Vector2i(static_cast<int>(getMapMaxColumnIndex()), 0);
    mapPosition = abs(mapPosition);
    setPosition(getMapOffset() + sf::Vector2f{mapPosition.x * BLOCK_WIDTH,
                                              mapPosition.y * BLOCK_WIDTH});
  }

  const auto tilePosition = mapPosition + direction;

  if (map[tilePosition.y][tilePosition.x] <= MapType::SlowDown) {
    mapPosition = tilePosition;
    destination = getMapOffset() + sf::Vector2f(tilePosition.x * BLOCK_WIDTH,
                                                tilePosition.y * BLOCK_WIDTH);
    return true;
  }

  return false;
}

void PacMan::restart() {
  mapPosition = START_POSITION;
  setPosition(getMapOffset() + sf::Vector2f(mapPosition.x * BLOCK_WIDTH,
                                            mapPosition.y * BLOCK_WIDTH));
  setDirection(START_DIRECTION);
  nextDirection = direction;
  destination = getPosition();
}

sf::Vector2i PacMan::getMapPosition() const { return mapPosition; }

sf::Vector2i PacMan::getDirection() const { return direction; }
