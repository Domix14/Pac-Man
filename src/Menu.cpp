#include "Menu.h"
#include "Map.h"
#include "PacManGame.h"
#include "ResourceManager.h"


#include <fstream>

Menu::Menu(Game *game) : Entity(game), currentText(0), keyPressed(false) {
  logoSprite.setPosition(sf::Vector2f(140.f, 100.f));
  bestScoreText.setCharacterSize(40);
  bestScoreText.setPosition(sf::Vector2f(220.f, 350.f));
  bestScoreText.setString("Best score: 0");

  menuTexts[0].setPosition(sf::Vector2f(250.f, 500.f));
  menuTexts[0].setString("Start");
  menuTexts[0].setCharacterSize(70);
  menuTexts[0].setFillColor(sf::Color::Red);

  menuTexts[1].setPosition(sf::Vector2f(266.f, 600.f));
  menuTexts[1].setString("Exit");
  menuTexts[1].setCharacterSize(70);
}

void Menu::update(float deltaTime) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !keyPressed) {
    menuTexts[currentText].setFillColor(sf::Color::White);
    currentText = ((--currentText) + menuTexts.size()) % menuTexts.size();
    menuTexts[currentText].setFillColor(sf::Color::Red);
    keyPressed = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !keyPressed) {
    menuTexts[currentText].setFillColor(sf::Color::White);
    currentText = (++currentText) % menuTexts.size();
    menuTexts[currentText].setFillColor(sf::Color::Red);
    keyPressed = true;
  } else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
             !sf::Keyboard::isKeyPressed(sf::Keyboard::S) && keyPressed) {
    keyPressed = false;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    auto game = dynamic_cast<PacManGame *>(getGame());
    switch (currentText) {
    case 0:
      game->startGame();
      break;
    case 1:
      game->exit();
      break;
    }
  }
}

void Menu::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadTexture("logo", "resources/graphics/logo.png");
  logoSprite.setTexture(resourceManager->getTexture("logo"));

  resourceManager->loadFont("font", "resources/fonts/font.otf");
  menuTexts[0].setFont(resourceManager->getFont("font"));
  menuTexts[1].setFont(resourceManager->getFont("font"));
  bestScoreText.setFont(resourceManager->getFont("font"));
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(logoSprite, states);
  target.draw(bestScoreText, states);
  target.draw(menuTexts[0], states);
  target.draw(menuTexts[1], states);
}

void Menu::setBestScore(size_t score) {
  bestScoreText.setString("Best score: " + std::to_string(score));
}
