#pragma once
#include "Game.h"

class GameCPUAlt :
    public Game
{
private:
	std::vector<int> getNeighboursIndices(int);
	void process();
public:
	GameCPUAlt(int dimension, int cellsPerDim) : Game(dimension, cellsPerDim) {};

};

