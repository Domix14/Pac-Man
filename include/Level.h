#pragma once
#include "Entity.h"

//#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
class Level :
    public Entity
{
public:
	Level(class Game* game);
	
	void update(float deltaTime) override;
	void beginPlay() override;
	void loadResources(ResourceManager* resourceManager) override;
	void onCollision(Entity* otherEntity) override;

private:
};

