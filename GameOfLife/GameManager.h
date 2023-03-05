#pragma once

#include "GraphicsDisplay.h"
#include "Game.h"

class GameManager
{
private:
	GraphicsDisplay* graphicsDisplay;

	Game* gameInstance;

public:
	GameManager(int, int);

	void run();
	
	~GameManager();
};

