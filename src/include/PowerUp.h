#pragma once
#include "Entity.h"

class PowerUp : public Entity {
public:
  PowerUp(class Game *game);

  void loadResources(ResourceManager *resourceManager) override;

  void update(float deltaTime) override{};
  void onCollision(Entity *otherEntity) override{};

  void beginPlay() override{};
};
