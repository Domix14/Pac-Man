#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class Animation
{
public:
	void update(float deltaTime, sf::Sprite& sprite);
	void setFrameTime(float time);
	void addSprites(const std::string& name, const std::vector<sf::Sprite>& sprites);
private:
	void nextFrame();

	std::string currentAnimation;
	std::unordered_map<std::string, std::vector<sf::Sprite>> m_sprites;
	float m_timer;
	float m_frameTime;
	size_t m_frame;
	
};

