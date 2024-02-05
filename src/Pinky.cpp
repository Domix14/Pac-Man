// #include "Pinky.h"
//
// #include "Utilities.h"
// #include "PacMan.h"
// #include "ResourceManager.h"
//
// Pinky::Pinky(Game* game, const PacMan* pacMan) :
//	Ghost(game), pacMan(pacMan)
//{
//	ghostHouse.emplace_back(11, 12);
//	ghostHouse.emplace_back(11, 13);
//
//	scatterPath.emplace_back(6, 5);
//	scatterPath.emplace_back(6, 4);
//	scatterPath.emplace_back(6, 3);
//	scatterPath.emplace_back(6, 2);
//	scatterPath.emplace_back(6, 1);
//	scatterPath.emplace_back(5, 1);
//	scatterPath.emplace_back(4, 1);
//	scatterPath.emplace_back(3, 1);
//	scatterPath.emplace_back(2, 1);
//	scatterPath.emplace_back(2, 2);
//	scatterPath.emplace_back(2, 3);
//	scatterPath.emplace_back(2, 4);
//	scatterPath.emplace_back(2, 5);
//	scatterPath.emplace_back(3, 5);
//	scatterPath.emplace_back(4, 5);
//	scatterPath.emplace_back(5, 5);
//
//	stateProperties[GhostState::GhostHouse] = GhostStateProperties(0.f,
//GhostState::ExitGhostHouse); 	stateProperties[GhostState::Eaten] =
//GhostStateProperties(20.f, GhostState::ExitGhostHouse);
//	stateProperties[GhostState::ExitGhostHouse] = GhostStateProperties(20.f,
//GhostState::GlobalState); 	stateProperties[GhostState::Frightened] =
//GhostStateProperties(10.f, GhostState::GlobalState);
// }
//
// void Pinky::findChaseDirection()
//{
//	goToTarget(pacMan->getMapPosition() + (pacMan->getDirection() * 4));
// }
//
//
// void Pinky::loadResources(ResourceManager* resourceManager)
//{
//	resourceManager->loadTexture("pinky",
//"resources/graphics/pinky_anim.png");
//	sprite.setTexture(resourceManager->getTexture("pinky"));
// }
