#pragma once

#include "Game.h"

#include "PacMan.h"
#include "Coin.h"
#include "Level.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "ScoreText.h"
#include "PowerUp.h"
#include "Menu.h"

#include <unordered_map>

enum GameState
{
	Exit = -1,
	NewGame = 0,
	Scatter = 1,
	Chase = 2,
	Frightened = 3,
	Dead = 4
};

struct StateProperties
{
	StateProperties(float dur, int first, int last, GameState next, GhostState ghost) :
		duration(dur), firstLevel(first), lastLevel(last), nextState(next), ghostState(ghost) {}
	float duration;
	int firstLevel;
	int lastLevel;
	GameState nextState;
	GhostState ghostState;
};

class PacManGame : public Game
{
public:
	PacManGame();
	~PacManGame();
	void launch() override;
	void update(float deltaTime) override;
	
	void exit();
	void openMenu();
	void closeGame();
	void startGame();
	void spawnCoins();
	void addScore(size_t score);
	void killPacMan();
	void resetPositions();
	void resetGame();
	void resetLevel();
	void changeState(GameState state);
	void updateState(float deltaTime);
	void pickCoin();
	void pickPowerUp();
private:
	GameState m_state;
	std::unordered_map<GameState, std::vector<StateProperties>> m_statesProperties;
	int m_currentLevel;
	float m_stateTimer;
	
	Menu m_menu;

	PacMan m_pacMan;
	Blinky m_blinky;
	Clyde m_clyde;
	Pinky m_pinky;
	Inky m_inky;
	std::vector<Coin> m_coins;
	std::vector<PowerUp> m_powers;
	Level m_level;
	ScoreText m_scoreText;
	
	size_t m_score;
	int m_lives;
	int m_coinCount;
};

