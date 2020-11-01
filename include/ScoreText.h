#pragma once
#include "Entity.h"
class ScoreText :
	public Entity
{
public:
	ScoreText(class Game* game);
	
	virtual void loadResources(ResourceManager* resourceManager) override;
	virtual void update(float deltaTime) override;
	virtual void beginPlay() override;
	virtual void onCollision(Entity* otherEntity) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateScore(size_t newScore);
protected:
	sf::Text m_scoreText;
};

