#pragma once

#include "Game.h"

#include "Coin.h"
#include "Ghost.h"
#include "Level.h"
#include "Menu.h"
#include "PacMan.h"
#include "PowerUp.h"
#include "Text.h"


#include <unordered_map>

enum GameState {
  Exit = -1,
  NewGame = 0,
  Scatter = 1,
  Chase = 2,
  Frightened = 3,
  Dead = 4
};

struct StateProperties {
  StateProperties(float dur, int first, int last, GameState next,
                  GhostState ghost)
      : duration(dur), firstLevel(first), lastLevel(last), nextState(next),
        ghostState(ghost) {}
  float duration;
  int firstLevel;
  int lastLevel;
  GameState nextState;
  GhostState ghostState;
};

class PacManGame : public Game {
public:
  PacManGame();
  void launch() override;
  void update(float deltaTime) override;

  void exit();
  void pickCoin();
  void openMenu();
  void closeGame();
  void startGame();
  void addScore(size_t score);
  void killPacMan();
  void pickPowerUp();

private:
  void resetGame();
  void resetLevel();
  void changeState(GameState state);
  void updateState(float deltaTime);
  void resetPositions();
  void spawnCoins();

  void saveScore() const;
  void loadScore();

  GameState state;
  std::unordered_map<GameState, std::vector<StateProperties>> statesProperties;
  int currentLevel;
  float stateTimer;

  Menu menu;

  PacMan pacMan;
  Blinky blinky;
  Clyde clyde;
  Pinky pinky;
  Inky inky;
  std::vector<Coin> coins;
  std::vector<PowerUp> powers;
  Level level;
  Text scoreText;
  Text livesText;

  size_t score;
  size_t bestScore;
  int lives;
  int coinCount;
};
