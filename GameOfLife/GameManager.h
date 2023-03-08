#pragma once

#include "GraphicsDisplay.h"
#include "Game.h"

class GameManager
{
private:
	GraphicsDisplay* m_graphicsDisplay;

	Game* m_gameInstance;

public:
	GameManager(int, int, ProcessMode);

	void run();
	
	~GameManager();
};

