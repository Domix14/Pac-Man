#pragma once
#include "Entity.h"

class PowerUp :
	public Entity
{
public:
	PowerUp(class Game* game);

	virtual void loadResources(ResourceManager* resourceManager) override;
	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;
};

