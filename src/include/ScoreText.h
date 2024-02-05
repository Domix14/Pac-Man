#pragma once
#include "Entity.h"
class ScoreText : public Entity {
public:
  ScoreText(class Game *game);

  void loadResources(ResourceManager *resourceManager) override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void updateScore(size_t newScore);

protected:
  sf::Text scoreText;
};
