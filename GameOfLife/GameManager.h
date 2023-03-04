#pragma once

#include "GameView.h"
#include "Game.h"

class GameManager
{
private:
	GameView* gameView;

	Game* gameInstance;

public:
	GameManager(int, int);

	void run();
	
	~GameManager();
};

