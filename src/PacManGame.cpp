#include "PacManGame.h"

#include "Engine.h"
#include "Map.h"


#include <fstream>

PacManGame::PacManGame()
    : Game(WINDOW_WIDTH, WINDOW_HEIGHT, "Pac-Man"), currentLevel(0), menu(this),
      pacMan(this), blinky(this, &pacMan), pinky(this, &pacMan),
      clyde(this, &pacMan), inky(this, &pacMan, &blinky), level(this),
      scoreText(this, 20, sf::Vector2f(0.f, 0.f)),
      livesText(this, 20, sf::Vector2f(550.f, 0.f)), score(0) {
  statesProperties[NewGame].emplace_back(0.f, 0, 1, GameState::Scatter,
                                         GhostState::Scatter);
  statesProperties[Scatter].emplace_back(10.f, 0, 1, GameState::Chase,
                                         GhostState::Scatter);
  statesProperties[Chase].emplace_back(20.f, 0, 1, GameState::Scatter,
                                       GhostState::Chase);
}

void PacManGame::launch() {
  loadScore();
  openMenu();
}

void PacManGame::update(float deltaTime) { updateState(deltaTime); }

void PacManGame::exit() { getEngine()->close(); }

void PacManGame::openMenu() {
  getEngine()->addEntity(&menu);
  menu.setBestScore(bestScore);
}

void PacManGame::closeGame() {
  level.destroy();
  livesText.destroy();
  blinky.destroy();
  scoreText.destroy();
  pacMan.destroy();
  pinky.destroy();
  clyde.destroy();
  inky.destroy();

  for (auto &c : coins) {
    c.destroy();
  }

  for (auto &p : powers) {
    p.destroy();
  }
}

void PacManGame::startGame() {
  menu.destroy();

  getEngine()->addEntity(&level);
  getEngine()->addEntity(&scoreText);
  getEngine()->addEntity(&livesText);
  getEngine()->addEntity(&pacMan);
  getEngine()->addEntity(&blinky);
  getEngine()->addEntity(&pinky);
  getEngine()->addEntity(&clyde);
  getEngine()->addEntity(&inky);
  spawnCoins();

  resetGame();
}

void PacManGame::spawnCoins() {
  coins.reserve(40);
  for (size_t x = 0; x < getMapMaxColumnIndex(); x++) {
    for (size_t y = 0; y < getMapMaxRowIndex(); y++) {
      if (map[y][x] == MapType::Move) {
        coins.emplace_back(this);
        coins.back().setPosition(
            getMapOffset() + sf::Vector2f(x * BLOCK_WIDTH, y * BLOCK_WIDTH));
      } else if (map[y][x] == MapType::PowerUpPosition) {
        powers.emplace_back(this);
        powers.back().setPosition(
            getMapOffset() + sf::Vector2f(x * BLOCK_WIDTH, y * BLOCK_WIDTH));
      }
    }
  }

  for (auto &coin : coins) {
    getEngine()->addEntity(&coin);
  }

  for (auto &Power : powers) {
    getEngine()->addEntity(&Power);
  }
}

void PacManGame::addScore(size_t score) {
  score += score;
  scoreText.setText("Score: " + std::to_string(score));
}

void PacManGame::killPacMan() {
  lives--;
  livesText.setText("Lives: " + std::to_string(lives));
  if (lives < 0) {
    if (score > bestScore) {
      bestScore = score;
      saveScore();
    }
    resetGame();
    openMenu();
    closeGame();
  } else {
    resetPositions();
  }
}

void PacManGame::resetPositions() {
  pacMan.restart();
  blinky.restart();
  pinky.restart();
  inky.restart();
  clyde.restart();
  changeState(GameState::NewGame);
}

void PacManGame::resetGame() {
  lives = 1;
  resetLevel();
  livesText.setText("Lives: " + std::to_string(lives));
  scoreText.setText("Score: " + std::to_string(score));
}

void PacManGame::resetLevel() {
  resetPositions();
  coinCount = 219;
}

void PacManGame::changeState(GameState state) {
  auto &properties = statesProperties[state];
  for (auto &p : properties) {
    if (p.firstLevel <= currentLevel && p.lastLevel >= currentLevel) {
      state = state;
      stateTimer = p.duration;
      blinky.changeGlobalState(p.ghostState);
      pinky.changeGlobalState(p.ghostState);
      inky.changeGlobalState(p.ghostState);
      clyde.changeGlobalState(p.ghostState);
    }
  }
}

void PacManGame::updateState(float deltaTime) {
  stateTimer -= deltaTime;
  if (stateTimer <= 0.f) {
    auto &properties = statesProperties[state];
    for (auto &p : properties) {
      if (p.firstLevel <= currentLevel && p.lastLevel >= currentLevel) {
        changeState(p.nextState);
      }
    }
  }
}

void PacManGame::pickCoin() {
  addScore(10);
  coinCount--;
  if (coinCount == 0) {
    resetLevel();
  }
}

void PacManGame::pickPowerUp() {
  addScore(10);
  blinky.changeState(GhostState::Frightened);
  pinky.changeState(GhostState::Frightened);
  inky.changeState(GhostState::Frightened);
  clyde.changeState(GhostState::Frightened);
}

void PacManGame::saveScore() const {
  std::ofstream file("best_score.txt");
  if (file.is_open()) {
    file << bestScore;
    file.close();
  }
}

void PacManGame::loadScore() {
  std::ifstream file("best_score.txt");
  if (file.is_open()) {
    file >> bestScore;
    file.close();
  }
}
