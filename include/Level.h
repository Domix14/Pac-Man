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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::vector<sf::RectangleShape> m_blocks;
};

