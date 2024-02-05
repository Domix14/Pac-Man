#include "Text.h"

#include "ResourceManager.h"

Text::Text(Game *game, unsigned fontSize, sf::Vector2f position)
    : Entity(game) {
  text.setCharacterSize(fontSize);
  text.setPosition(position);
}

void Text::loadResources(ResourceManager *resourceManager) {
  resourceManager->loadFont("font", "resources/fonts/font.otf");
  text.setFont(resourceManager->getFont("font"));
}

void Text::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(text, states);
}

void Text::setText(const std::string &newText) { text.setString(newText); }
