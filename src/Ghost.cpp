#include "Ghost.h"

#include "Map.h"
#include "PacMan.h"
#include "PacManGame.h"
#include "ResourceManager.h"
#include "Utilities.h"

#include <array>

sf::Vector2i Path::getNextMapPosition() {
  const auto position = mapPositions[positionIndex];
  positionIndex = (++positionIndex) % mapPositions.size();
  return position;
}

void Path::addPosition(sf::Vector2i position) {
  mapPositions.push_back(position);
  if (map[position.y][position.x] == MapType::Teleport) {
    position -= sf::Vector2i(static_cast<int>(getMapMaxColumnIndex()), 0);
    mapPositions.push_back(abs(position));
  }
}

Ghost::Ghost(Game *game)
    : Entity(game), START_POSITION({11, 12}), START_DIRECTION({0, 1}),
      MOVEMENT_SPEED(85.f), FAST_MOVEMENT_SPEED(500.f),
      SLOW_MOVEMENT_SPEED(65.f), path() {

  collisionRect.width = 15;
  collisionRect.height = 15;
  collisionRectOffset = {7.5f, 7.5f};
  bEnableCollision = true;

  animation.addRects("right",
                     {sf::IntRect(0, 0, 30, 30), sf::IntRect(30, 0, 30, 30)});
  animation.addRects("up",
                     {sf::IntRect(0, 30, 30, 30), sf::IntRect(30, 30, 30, 30)});
  animation.addRects("left",
                     {sf::IntRect(0, 60, 30, 30), sf::IntRect(30, 60, 30, 30)});
  animation.addRects("down",
                     {sf::IntRect(0, 90, 30, 30), sf::IntRect(30, 90, 30, 30)});
  animation.addRects("frightened", {sf::IntRect(0, 120, 30, 30),
                                    sf::IntRect(30, 120, 30, 30)});
  animation.setFrameTime(0.3f);
}

void Ghost::update(float deltaTime) {
  updateStateTimer(deltaTime);
  animation.update(deltaTime, sprite);
  const sf::Vector2f nextPosition =
      getPosition() +
      (static_cast<sf::Vector2f>(direction) * movementSpeed * deltaTime);
  if (length(nextPosition - destination) <
      length(getPosition() - destination)) {
    setPosition(nextPosition);
  } else {
    setPosition(destination);
    if (path.positionIndex != 0) {
      updateDirection();
    } else {
      findNextPosition();
    }
  }
}

void Ghost::onCollision(Entity *otherEntity) {
  const auto *pacMan = dynamic_cast<PacMan *>(otherEntity);
  if (pacMan) {
    if (ghostState == GhostState::Frightened) {
      changeState(GhostState::Eaten);
    } else if (ghostState != GhostState::Eaten) {
      auto *game = dynamic_cast<PacManGame *>(getGame());
      if (game) {
        game->killPacMan();
      }
    }
  }
}

void Ghost::changeGlobalState(GhostState newState) {
  globalGhostState = newState;
}

void Ghost::changeState(GhostState newState) {
  ghostState = newState;
  stateTimer = stateProperties[ghostState].duration;

  if (ghostState == GhostState::GlobalState &&
      map[mapPosition.y][mapPosition.x] == MapType::GhostHouse) {
    changeState(GhostState::ExitGhostHouse);
  }

  switch (ghostState) {
  case GhostState::Frightened: {
    animation.setAnimation("frightened", sprite);
    break;
  }
  case GhostState::Eaten: {
    movementSpeed = FAST_MOVEMENT_SPEED;
    break;
  }
  case GhostState::GhostHouse: {
    movementSpeed = MOVEMENT_SPEED;
    break;
  }
  default: {
    changeAnimation();
  }
  }
}

sf::Vector2i Ghost::getMapPosition() const { return mapPosition; }

void Ghost::updateDirection() {
  const auto nextMapPosition = path.getNextMapPosition();
  if (length(static_cast<sf::Vector2f>(nextMapPosition - mapPosition)) > 1.f) {
    mapPosition = nextMapPosition;
    destination = getMapOffset() + sf::Vector2f(mapPosition.x * BLOCK_WIDTH,
                                                mapPosition.y * BLOCK_WIDTH);
    setDirection(-direction);
    setPosition(getMapOffset() + sf::Vector2f(mapPosition.x * BLOCK_WIDTH,
                                              mapPosition.y * BLOCK_WIDTH));
  } else {
    setDirection(nextMapPosition - mapPosition);
    mapPosition = nextMapPosition;
    destination = getMapOffset() + sf::Vector2f(mapPosition.x * BLOCK_WIDTH,
                                                mapPosition.y * BLOCK_WIDTH);
  }

  if ((map[mapPosition.y][mapPosition.x] == MapType::SlowDown ||
       map[mapPosition.y][mapPosition.x] == MapType::Teleport ||
       map[mapPosition.y][mapPosition.x] == MapType::GhostHouseEntrance) &&
      ghostState != GhostState::Eaten) {
    movementSpeed = SLOW_MOVEMENT_SPEED;
  } else if (ghostState != GhostState::Eaten) {
    movementSpeed = MOVEMENT_SPEED;
  }
}

void Ghost::findNextPosition() {
  GhostState state = ghostState;
  if (ghostState == GhostState::GlobalState) {
    state = globalGhostState;
  }

  switch (state) {
  case GhostState::Scatter: {
    if (mapPosition != scatterPath[0]) {
      goToTarget(scatterPath[0]);
    } else {
      path.mapPositions = scatterPath;
      path.positionIndex = 0;
      updateDirection();
    }
    break;
  }
  case GhostState::Frightened: {
    auto directions = findAvailableDirections();

    if (!directions.empty()) {
      const int index = randRange(0, static_cast<int>(directions.size() - 1));
      goToTarget(mapPosition + *(std::next(directions.begin(), index)));
    }
    break;
  }
  case GhostState::Chase: {
    findChaseDirection();
    break;
  }
  case GhostState::Eaten: {
    if (mapPosition != ghostHouse[0]) {
      goToTarget(ghostHouse[0]);
    } else {
      changeState(GhostState::GhostHouse);
    }
    break;
  }
  case GhostState::GhostHouse: {
    if (mapPosition != ghostHouse[0] && mapPosition != ghostHouse[1]) {
      goToTarget(ghostHouse[0]);
    } else if (mapPosition == ghostHouse[0]) {
      goToTarget(ghostHouse[1]);
    } else if (mapPosition == ghostHouse[1]) {
      goToTarget(ghostHouse[0]);
    }
    break;
  }
  case GhostState::ExitGhostHouse: {
    if (map[mapPosition.y][mapPosition.x] == MapType::GhostHouse) {
      goToTarget(sf::Vector2i(11, 10));
    } else {
      changeState(GhostState::GlobalState);
    }
    break;
  }
  }
}

void Ghost::setDirection(sf::Vector2i nextDirection) {
  direction = nextDirection;
  changeAnimation();
}

void Ghost::changeAnimation() {
  if (ghostState == GhostState::Frightened)
    return;

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

void Ghost::goToTarget(sf::Vector2i position) {
  path.mapPositions.clear();
  path.positionIndex = 0;

  auto directions = findAvailableDirections();
  int bestIndex = -1;
  float bestDistance = 0.f;
  for (int i = 0; i < directions.size(); i++) {
    if (bestIndex == -1) {
      bestIndex = i;
      bestDistance = length(
          static_cast<sf::Vector2f>(position - (mapPosition + directions[i])));
    } else {
      const auto distance = length(
          static_cast<sf::Vector2f>(position - (mapPosition + directions[i])));
      if (distance < bestDistance) {
        bestIndex = i;
        bestDistance = distance;
      }
    }
  }

  path.addPosition(mapPosition + directions[bestIndex]);
  updateDirection();
}

bool Ghost::checkPosition(sf::Vector2i position) const {
  if (position.x < 0 || position.y < 0 || position.x > getMapMaxColumnIndex() ||
      position.y > getMapMaxRowIndex()) {
    return false;
  }

  if (map[position.y][position.x] <= MapType::GhostHouse &&
      (ghostState == GhostState::GhostHouse ||
       ghostState == GhostState::ExitGhostHouse ||
       ghostState == GhostState::Eaten)) {
    return true;
  } else if (map[position.y][position.x] <= MapType::SlowDown) {
    return true;
  }
  return false;
}

std::vector<sf::Vector2i> Ghost::findAvailableDirections() const {
  auto position = mapPosition;
  if (!path.mapPositions.empty()) {
    position = path.mapPositions.back();
  }

  std::vector<sf::Vector2i> availableDirections{
      {{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
  for (auto it = availableDirections.begin();
       it != availableDirections.end();) {
    if (*it == -direction || !checkPosition(position + *it)) {
      it = availableDirections.erase(it);
    } else {
      ++it;
    }
  }
  if (availableDirections.empty() ||
      map[mapPosition.y][mapPosition.x] == MapType::GhostHouse) {
    availableDirections.push_back(-direction);
  }
  return availableDirections;
}

void Ghost::exitGhostHouse() { goToTarget(sf::Vector2i(11, 11)); }

void Ghost::updateStateTimer(float deltaTime) {
  if (ghostState == GhostState::GlobalState)
    return;

  stateTimer -= deltaTime;
  if (stateTimer <= 0.f) {
    changeState(stateProperties[ghostState].nextState);
  }
}

void Ghost::restart() {
  changeState(GhostState::GhostHouse);
  mapPosition = ghostHouse[0];
  setPosition(getMapOffset() + sf::Vector2f(mapPosition.x * BLOCK_WIDTH,
                                            mapPosition.y * BLOCK_WIDTH));
  setDirection(sf::Vector2i(0, 1));
  goToTarget(ghostHouse[1]);
}

Blinky::Blinky(Game *game, const PacMan *pacMan) : Ghost(game), pacMan(pacMan) {
  ghostHouse.emplace_back(11, 12);
  ghostHouse.emplace_back(11, 13);

  scatterPath.emplace_back(16, 1);
  scatterPath.emplace_back(17, 1);
  scatterPath.emplace_back(18, 1);
  scatterPath.emplace_back(19, 1);
  scatterPath.emplace_back(20, 1);
  scatterPath.emplace_back(20, 2);
  scatterPath.emplace_back(20, 3);
  scatterPath.emplace_back(20, 4);
  scatterPath.emplace_back(20, 5);
  scatterPath.emplace_back(19, 5);
  scatterPath.emplace_back(18, 5);
  scatterPath.emplace_back(17, 5);
  scatterPath.emplace_back(16, 5);
  scatterPath.emplace_back(16, 4);
  scatterPath.emplace_back(16, 3);
  scatterPath.emplace_back(16, 2);

  stateProperties[GhostState::GhostHouse] =
      GhostStateProperties(0.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::Eaten] =
      GhostStateProperties(20.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::ExitGhostHouse] =
      GhostStateProperties(20.f, GhostState::GlobalState);
  stateProperties[GhostState::Frightened] =
      GhostStateProperties(10.f, GhostState::GlobalState);
}

void Blinky::findChaseDirection() { goToTarget(pacMan->getMapPosition()); }

void Blinky::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("blinky", "resources/graphics/blinky_anim.png");
  sprite.setTexture(resourceManager->getTexture("blinky"));
}

Clyde::Clyde(Game *game, const PacMan *pacMan) : Ghost(game), pacMan(pacMan) {
  ghostHouse.emplace_back(12, 12);
  ghostHouse.emplace_back(12, 13);

  scatterPath.emplace_back(6, 23);
  scatterPath.emplace_back(5, 23);
  scatterPath.emplace_back(4, 23);
  scatterPath.emplace_back(3, 23);
  scatterPath.emplace_back(2, 23);
  scatterPath.emplace_back(2, 24);
  scatterPath.emplace_back(2, 25);
  scatterPath.emplace_back(3, 25);
  scatterPath.emplace_back(4, 25);
  scatterPath.emplace_back(5, 25);
  scatterPath.emplace_back(6, 25);
  scatterPath.emplace_back(7, 25);
  scatterPath.emplace_back(8, 25);
  scatterPath.emplace_back(9, 25);
  scatterPath.emplace_back(10, 25);
  scatterPath.emplace_back(10, 24);
  scatterPath.emplace_back(10, 23);
  scatterPath.emplace_back(9, 23);
  scatterPath.emplace_back(8, 23);
  scatterPath.emplace_back(8, 22);
  scatterPath.emplace_back(8, 21);
  scatterPath.emplace_back(8, 20);
  scatterPath.emplace_back(7, 20);
  scatterPath.emplace_back(6, 20);
  scatterPath.emplace_back(6, 21);
  scatterPath.emplace_back(6, 22);

  stateProperties[GhostState::GhostHouse] =
      GhostStateProperties(10.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::Eaten] =
      GhostStateProperties(20.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::ExitGhostHouse] =
      GhostStateProperties(20.f, GhostState::GlobalState);
  stateProperties[GhostState::Frightened] =
      GhostStateProperties(10.f, GhostState::GlobalState);
}

void Clyde::findChaseDirection() {
  const auto distance = length(getPosition() - pacMan->getPosition());
  if (distance < 8 * BLOCK_WIDTH) {
    if (mapPosition != scatterPath[0]) {
      goToTarget(scatterPath[0]);
    } else {
      path.mapPositions = scatterPath;
      path.positionIndex = 0;
      updateDirection();
    }
  } else {
    goToTarget(pacMan->getMapPosition());
  }
}

void Clyde::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("clyde", "resources/graphics/clyde_anim.png");
  sprite.setTexture(resourceManager->getTexture("clyde"));
}

Inky::Inky(Game *game, const PacMan *pacMan, const Ghost *blinky)
    : Ghost(game), pacMan(pacMan), blinky(blinky) {
  ghostHouse.emplace_back(10, 12);
  ghostHouse.emplace_back(10, 13);

  scatterPath.emplace_back(16, 21);
  scatterPath.emplace_back(16, 22);
  scatterPath.emplace_back(16, 23);
  scatterPath.emplace_back(17, 23);
  scatterPath.emplace_back(18, 23);
  scatterPath.emplace_back(19, 23);
  scatterPath.emplace_back(20, 23);
  scatterPath.emplace_back(20, 24);
  scatterPath.emplace_back(20, 25);
  scatterPath.emplace_back(19, 25);
  scatterPath.emplace_back(18, 25);
  scatterPath.emplace_back(17, 25);
  scatterPath.emplace_back(16, 25);
  scatterPath.emplace_back(15, 25);
  scatterPath.emplace_back(14, 25);
  scatterPath.emplace_back(13, 25);
  scatterPath.emplace_back(12, 25);
  scatterPath.emplace_back(12, 24);
  scatterPath.emplace_back(12, 23);
  scatterPath.emplace_back(13, 23);
  scatterPath.emplace_back(14, 23);
  scatterPath.emplace_back(14, 22);
  scatterPath.emplace_back(14, 21);
  scatterPath.emplace_back(14, 20);
  scatterPath.emplace_back(15, 20);
  scatterPath.emplace_back(16, 20);

  stateProperties[GhostState::GhostHouse] =
      GhostStateProperties(10.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::Eaten] =
      GhostStateProperties(20.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::ExitGhostHouse] =
      GhostStateProperties(20.f, GhostState::GlobalState);
  stateProperties[GhostState::Frightened] =
      GhostStateProperties(10.f, GhostState::GlobalState);
}

void Inky::findChaseDirection() {
  auto direction = blinky->getMapPosition() - pacMan->getMapPosition();
  goToTarget(pacMan->getMapPosition() - direction);
}

void Inky::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("inky", "resources/graphics/inky_anim.png");
  sprite.setTexture(resourceManager->getTexture("inky"));
}

Pinky::Pinky(Game *game, const PacMan *pacMan) : Ghost(game), pacMan(pacMan) {
  ghostHouse.emplace_back(11, 12);
  ghostHouse.emplace_back(11, 13);

  scatterPath.emplace_back(6, 5);
  scatterPath.emplace_back(6, 4);
  scatterPath.emplace_back(6, 3);
  scatterPath.emplace_back(6, 2);
  scatterPath.emplace_back(6, 1);
  scatterPath.emplace_back(5, 1);
  scatterPath.emplace_back(4, 1);
  scatterPath.emplace_back(3, 1);
  scatterPath.emplace_back(2, 1);
  scatterPath.emplace_back(2, 2);
  scatterPath.emplace_back(2, 3);
  scatterPath.emplace_back(2, 4);
  scatterPath.emplace_back(2, 5);
  scatterPath.emplace_back(3, 5);
  scatterPath.emplace_back(4, 5);
  scatterPath.emplace_back(5, 5);

  stateProperties[GhostState::GhostHouse] =
      GhostStateProperties(0.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::Eaten] =
      GhostStateProperties(20.f, GhostState::ExitGhostHouse);
  stateProperties[GhostState::ExitGhostHouse] =
      GhostStateProperties(20.f, GhostState::GlobalState);
  stateProperties[GhostState::Frightened] =
      GhostStateProperties(10.f, GhostState::GlobalState);
}

void Pinky::findChaseDirection() {
  goToTarget(pacMan->getMapPosition() + (pacMan->getDirection() * 4));
}

void Pinky::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("pinky", "resources/graphics/pinky_anim.png");
  sprite.setTexture(resourceManager->getTexture("pinky"));
}
