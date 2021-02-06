#pragma once

#include <string>
/*Base class for game*/

class Game
{
public:
	Game(size_t width, size_t height, const std::string& title);

	virtual void launch() {}
	virtual void update(float deltaTime) {}
	size_t getWindowWidth() const;
	size_t getWindowHeight() const;
	std::string getTitle() const;
	void setEngine(class Engine* engine);
	class Engine* getEngine() const;
	
private:
	size_t m_windowWidth;
	size_t m_windowHeight;
	std::string m_title;
	class Engine* m_engine;
};

