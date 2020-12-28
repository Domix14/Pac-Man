#include "Entity.h"

Entity::Entity(Game* game) :
	m_game(game),
	m_bAlive(true),
	m_bDraw(true),
	m_bEnableCollision(false),
	m_bDrawCollisionRect(false)
{
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bDraw)
	{
		target.draw(m_sprite, states);
	}

	if(m_bDrawCollisionRect)
	{
		sf::VertexArray vertexRect(sf::PrimitiveType::LinesStrip, 4);
		vertexRect[0] = sf::Vertex(m_collisionRect.getPosition(), sf::Color::Red);
		vertexRect[1] = sf::Vertex(m_collisionRect.getPosition() + sf::Vector2f(m_collisionRect.width, 0.f), sf::Color::Red);
		vertexRect[2] = sf::Vertex(m_collisionRect.getPosition() + sf::Vector2f(m_collisionRect.width, m_collisionRect.height), sf::Color::Red);
		vertexRect[3] = sf::Vertex(m_collisionRect.getPosition() + sf::Vector2f(0.f, m_collisionRect.height), sf::Color::Red);
		
		target.draw(vertexRect, states);
	}
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
	m_collisionRect.left = position.x;
	m_collisionRect.top = position.y;
}

bool Entity::isCollisionEnabled()
{
	return m_bEnableCollision;
}

sf::FloatRect Entity::getCollisionRect() const
{
	return m_collisionRect;
}

bool Entity::isAlive() const
{
	return m_bAlive;
}

void Entity::destroy()
{
	m_bAlive = false;
}

void Entity::reset()
{
	m_bAlive = true;
}

Game* Entity::getGame() const
{
	return m_game;
}
