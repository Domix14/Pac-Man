#include "Blinky.h"

#include "PacMan.h"
#include "ResourceManager.h"
#include "Utilities.h"


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
