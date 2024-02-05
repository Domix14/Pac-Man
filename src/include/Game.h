#pragma once

#include <string>
/*Base class for game*/

class Game {
public:
  Game(size_t width, size_t height, const std::string &title);

  /*Launch the game*/
  virtual void launch() {}

  /*Called every frame*/
  virtual void update(float deltaTime) {}

  /*Returns window width*/
  size_t getWindowWidth() const;

  /*Returns window height*/
  size_t getWindowHeight() const;

  /*Returns game title*/
  std::string getTitle() const;

  /*Set engine pointer*/
  void setEngine(class Engine *engine);

  /*Returns engine pointer*/
  class Engine *getEngine() const;

private:
  size_t windowWidth;
  size_t windowHeight;
  std::string title;
  class Engine *engine;
};
