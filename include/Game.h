#pragma once

#include "Engine.h"

/*Base class for game*/

class Game
{
public:
	Game(size_t width, size_t height, const std::string& title);

	virtual void launch();
	virtual void update(float deltaTime);
	const Engine* getEngine() const;
	
	
	
protected:
	Engine m_engine;
};

