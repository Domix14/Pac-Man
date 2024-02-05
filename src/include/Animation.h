#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

class Animation {
public:
  Animation() = default;

  /*Update animation, should be called every frame*/
  void update(float deltaTime, sf::Sprite &sprite);

  /*Set how long one frame is displayed*/
  void setFrameTime(float time);

  /*Add animation frame from texture*/
  void addRects(const std::string &name, const std::vector<sf::IntRect> &rects);

  /*Set current animation frames*/
  void setAnimation(const std::string &name, sf::Sprite &sprite);

private:
  void nextFrame();

  std::string currentAnimation;
  std::unordered_map<std::string, std::vector<sf::IntRect>> textureRects;
  float timer;
  float frameTime;
  size_t currentFrame;
};
