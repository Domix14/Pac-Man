#include "ScoreText.h"

#include "Game.h"
#include "ResourceManager.h"


ScoreText::ScoreText(Game *game) : Entity(game) {
  setPosition(sf::Vector2f(0.f, 0.f));
  scoreText.setCharacterSize(20);
  scoreText.setString("Score: 0");
}

void ScoreText::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadFont("font", "resources/fonts/font.otf");
  scoreText.setFont(resourceManager->getFont("font"));
}

void ScoreText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(scoreText, states);
}

void ScoreText::updateScore(size_t newScore) {
  scoreText.setString("Score: " + std::to_string(newScore));
}
