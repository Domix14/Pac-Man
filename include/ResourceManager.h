#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <string>



class ResourceManager
{
public:
	void loadTexture(const std::string& textureName, const std::string& texturePath);
	const sf::Texture& getTexture(const std::string& textureName);
private:
	std::unordered_map<std::string, sf::Texture> m_textures;
};

