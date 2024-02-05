#include "ResourceManager.h"

#include <iostream>

void ResourceManager::loadTexture(const std::string &textureName,
                                  const std::string &texturePath) {
  if (textures.find(textureName) != textures.end())
    return;

  sf::Texture newTexture;
  if (newTexture.loadFromFile(texturePath)) {
    textures[textureName] = newTexture;
  } else {
    std::cout << "Failed to find texture";
  }
}

const sf::Texture &ResourceManager::getTexture(const std::string &textureName) {
  if (textures.find(textureName) != textures.end()) {
    return textures[textureName];
  } else {
    return textures[textureName] = sf::Texture();
  }
}

void ResourceManager::loadFont(const std::string &fontName,
                               const std::string &fontPath) {
  if (fonts.find(fontName) != fonts.end())
    return;

  sf::Font newFont;
  if (newFont.loadFromFile(fontPath)) {
    fonts[fontName] = newFont;
  } else {
    std::cout << "Failed to find font";
  }
}

const sf::Font &ResourceManager::getFont(const std::string &fontName) {
  if (fonts.find(fontName) != fonts.end()) {
    return fonts[fontName];
  } else {
    return fonts[fontName] = sf::Font();
  }
}
