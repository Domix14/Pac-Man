#include "Entity.h"

Entity::Entity(Game* game) :
	m_game(game)
{
}

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

Game* Entity::getGame() const
{
	return m_game;
}
