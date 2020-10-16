#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float deltaTime) = 0;
	
	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	
protected:
	sf::Sprite m_sprite;

};

