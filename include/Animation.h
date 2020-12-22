#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class Animation
{
public:
	Animation();
	void update(float deltaTime, sf::Sprite& sprite);
	void setFrameTime(float time);
	void addRects(const std::string& name, const std::vector<sf::IntRect>& rects);
	void setAnimation(const std::string& name, sf::Sprite& sprite);
private:
	void nextFrame();

	std::string currentAnimation;
	std::unordered_map<std::string, std::vector<sf::IntRect>> m_textureRects;
	float m_timer;
	float m_frameTime;
	size_t m_frame;
	
};

