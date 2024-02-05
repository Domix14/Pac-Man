#pragma once
#include "Entity.h"

class Level : public Entity {
public:
  Level(class Game *game);

  void loadResources(ResourceManager *resourceManager) override;
  void update(float deltaTime) override{};
  void onCollision(Entity *otherEntity) override{};

  void beginPlay() override{};
};
