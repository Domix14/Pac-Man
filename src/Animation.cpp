#include "Animation.h"

void Animation::update(float deltaTime, sf::Sprite& sprite)
{
	m_timer -= deltaTime;
	if(m_timer <= 0.f)
	{
		nextFrame();
		sprite = m_sprites[currentAnimation][m_frame];
		m_timer = m_frameTime;
	}
}

void Animation::setFrameTime(float time)
{
	m_frameTime = time;
}

void Animation::addSprites(const std::string& name, const std::vector<sf::Sprite>& sprites)
{
	m_sprites[name] = sprites;
}

void Animation::nextFrame()
{
	if(m_frame == m_sprites[currentAnimation].size() - 1)
	{
		m_frame = 0;
	}
	else
	{
		m_frame++;
	}
}
