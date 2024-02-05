#pragma once
#include "Entity.h"
#include <array>
class Menu : public Entity {
public:
  Menu(class Game *game);

  void update(float deltaTime) override;
  void loadResources(ResourceManager *resourceManager) override;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void onCollision(Entity *otherEntity) override{};
  void beginPlay() override{};

  /*Set score showed on screen*/
  void setBestScore(size_t score);

private:
  sf::Sprite logoSprite;
  sf::Text startText;
  sf::Text exitText;
  sf::Text bestScoreText;
  std::array<sf::Text, 2> menuTexts;
  bool keyPressed;
  size_t currentText;
};
