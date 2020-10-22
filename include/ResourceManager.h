#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <unordered_map>
#include <string>



class ResourceManager
{
public:
	void loadTexture(const std::string& textureName, const std::string& texturePath);
	const sf::Texture& getTexture(const std::string& textureName);

	void loadFont(const std::string& fontName, const std::string& fontPath);
	const sf::Font& getFont(const std::string& fontName);
private:
	std::unordered_map<std::string, sf::Texture> m_textures;
	std::unordered_map<std::string, sf::Font> m_fonts;
};

