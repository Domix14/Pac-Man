#pragma once

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	Entity(class Game* game);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void update(float deltaTime) = 0;
	
	const sf::Sprite& getSprite() const;
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);
	
protected:
	class Game* getGame() const;
	
	sf::Sprite m_sprite;

private:
	class Game* m_game;

};

