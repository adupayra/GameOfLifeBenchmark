#pragma once
#include "Game.h"

class GameCPU: public Game
{
private:
	void process();
public:
	GameCPU(int dimension, int cellsPerDim) : Game(dimension, cellsPerDim) {};
};

