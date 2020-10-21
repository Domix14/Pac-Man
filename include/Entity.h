#pragma once

#include <SFML/Graphics.hpp>



class Entity : public sf::Drawable
{
public:
	Entity(class Game* game);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void beginPlay() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void loadResources(class ResourceManager* resourceManager) = 0;
	virtual void onCollision(Entity* otherEntity) = 0;
	
	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	bool isCollisionEnabled();
	sf::FloatRect getCollisionRect() const;
	bool isAlive() const;
	void destroy();
protected:
	class Game* getGame() const;

	bool m_bAlive;
	
	bool m_bDraw;
	sf::Sprite m_sprite;

	bool m_bEnableCollision;
	bool m_bDrawCollisionRect;
	sf::FloatRect m_collisionRect;
private:
	class Game* m_game;

};

