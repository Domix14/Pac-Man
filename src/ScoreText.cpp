#include "ScoreText.h"

#include "ResourceManager.h"
#include "Game.h"

ScoreText::ScoreText(Game* game) :
	Entity(game)
{
	
}

void ScoreText::loadResources(ResourceManager* resourceManager)
{
	resourceManager->loadFont("font", "resources/fonts/font.otf");
	m_scoreText.setFont(resourceManager->getFont("font"));
}

void ScoreText::update(float deltaTime)
{
}

void ScoreText::beginPlay()
{
	setPosition(sf::Vector2f(0.f, 0.f));
	m_scoreText.setCharacterSize(20);
	m_scoreText.setString("Score: 0");
}

void ScoreText::onCollision(Entity* otherEntity)
{
}

void ScoreText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_scoreText, states);
}

void ScoreText::updateScore(size_t newScore)
{
	m_scoreText.setString("Score: " + std::to_string(newScore));
}
