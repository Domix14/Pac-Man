//#include "Pinky.h"
//
//#include "Utilities.h"
//#include "PacMan.h"
//#include "ResourceManager.h"
//
//Pinky::Pinky(Game* game, const PacMan* pacMan) :
//	Ghost(game), m_pacMan(pacMan)
//{
//	m_ghostHouse.emplace_back(11, 12);
//	m_ghostHouse.emplace_back(11, 13);
//
//	m_scatterPath.emplace_back(6, 5);
//	m_scatterPath.emplace_back(6, 4);
//	m_scatterPath.emplace_back(6, 3);
//	m_scatterPath.emplace_back(6, 2);
//	m_scatterPath.emplace_back(6, 1);
//	m_scatterPath.emplace_back(5, 1);
//	m_scatterPath.emplace_back(4, 1);
//	m_scatterPath.emplace_back(3, 1);
//	m_scatterPath.emplace_back(2, 1);
//	m_scatterPath.emplace_back(2, 2);
//	m_scatterPath.emplace_back(2, 3);
//	m_scatterPath.emplace_back(2, 4);
//	m_scatterPath.emplace_back(2, 5);
//	m_scatterPath.emplace_back(3, 5);
//	m_scatterPath.emplace_back(4, 5);
//	m_scatterPath.emplace_back(5, 5);
//
//	m_stateProperties[GhostState::GhostHouse] = GhostStateProperties(0.f, GhostState::ExitGhostHouse);
//	m_stateProperties[GhostState::Eaten] = GhostStateProperties(20.f, GhostState::ExitGhostHouse);
//	m_stateProperties[GhostState::ExitGhostHouse] = GhostStateProperties(20.f, GhostState::GlobalState);
//	m_stateProperties[GhostState::Frightened] = GhostStateProperties(10.f, GhostState::GlobalState);
//}
//
//void Pinky::findChaseDirection()
//{
//	goToTarget(m_pacMan->getMapPosition() + (m_pacMan->getDirection() * 4));
//}
//
//
//void Pinky::loadResources(ResourceManager* resourceManager)
//{
//	resourceManager->loadTexture("pinky", "resources/graphics/pinky_anim.png");
//	m_sprite.setTexture(resourceManager->getTexture("pinky"));
//}
