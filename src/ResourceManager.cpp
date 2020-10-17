#include "ResourceManager.h"

#include <iostream>

void ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	sf::Texture newTexture;
	if(newTexture.loadFromFile(texturePath))
	{
		m_textures[textureName] = newTexture;
	}
	else
	{
		std::cout << "Failed to find texture";
	}
}

const sf::Texture& ResourceManager::getTexture(const std::string& textureName)
{
	if(m_textures.find(textureName) != m_textures.end())
	{
		return m_textures[textureName];
	}
	else
	{
		return m_textures[textureName] = sf::Texture();
	}
}
