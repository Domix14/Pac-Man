#include "Animation.h"

#include "Utilities.h"

void Animation::update(float deltaTime, sf::Sprite &sprite) {
  if (frameTime <= 1e-8)
    return;

  timer -= deltaTime;
  if (timer <= 0.f) {
    nextFrame();
    if (textureRects.find(currentAnimation) != textureRects.end()) {
      sprite.setTextureRect(textureRects[currentAnimation][frameTime]);
    }
    timer = frameTime;
  }
}

void Animation::setFrameTime(float time) { frameTime = time; }

void Animation::addRects(const std::string &name,
                         const std::vector<sf::IntRect> &rects) {
  textureRects[name] = rects;
}

void Animation::setAnimation(const std::string &name, sf::Sprite &sprite) {
  if (textureRects.find(name) != textureRects.end()) {
    currentAnimation = name;
    sprite.setTextureRect(textureRects[currentAnimation][frameTime]);
  }
}

void Animation::nextFrame() {
  if (frameTime == textureRects[currentAnimation].size() - 1) {
    frameTime = 0;
  } else {
    frameTime++;
  }
}
