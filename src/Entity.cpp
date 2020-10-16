#include "Entity.h"

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

const sf::Sprite& Entity::getSprite() const
{
	return m_sprite;
}

sf::Vector2f Entity::getPosition() const
{
	return m_sprite.getPosition();
}

void Entity::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
