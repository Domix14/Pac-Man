#pragma once
#include "Entity.h"
#include <array>
class Menu :
    public Entity
{
public:
	Menu(class Game* game);

	void update(float deltaTime) override;
	void beginPlay() override;
	void loadResources(ResourceManager* resourceManager) override;
	void onCollision(Entity* otherEntity) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::Sprite m_logoSprite;
	sf::Text m_startText;
	sf::Text m_exitText;
	std::array<sf::Text, 2> m_menuTexts;
	bool m_keyPressed;
	size_t m_currentText;
};

