#pragma once
#include "Entity.h"
class Point :
    public Entity
{
public:
	Point(class Game* game);

	virtual void loadResources(ResourceManager* resourceManager) override;
	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;
};

