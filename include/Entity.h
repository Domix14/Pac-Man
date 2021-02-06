#pragma once

#include <SFML/Graphics.hpp>

enum CollisionChannel
{
	Player = 1,
	Enemy = 2,
	World = 3,
};

class Entity : public sf::Drawable
{
public:
	Entity(class Game* game);
	virtual ~Entity() {}
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void beginPlay() {}
	virtual void update(float deltaTime) {}
	virtual void loadResources(class ResourceManager* resourceManager) {}
	virtual void onCollision(Entity* otherEntity) {}
	
	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	
	bool isCollisionEnabled() const;
	sf::FloatRect getCollisionRect() const;
	bool isAlive() const;
	bool isMovable() const;
	void setAlive();
	void setPosition(sf::Vector2f position);
	void destroy();
protected:
	class Game* getGame() const;

	bool m_bDraw;
	bool m_bEnableCollision;
	bool m_bDrawCollisionRect;
	bool m_bMovable;
	
	sf::Sprite m_sprite;
	sf::Vector2f m_collisionRectOffset;
	sf::FloatRect m_collisionRect;
private:
	class Game* const m_game;

	bool m_bAlive;
};

