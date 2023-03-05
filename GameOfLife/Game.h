#pragma once
#include "LifeRules.h"
#include <vector>

class Game
{
private:
	int dimension;
	int nbCells;
	std::vector<int> cellsToChange;
	LifeRules* rules;

public:
	
	uint8_t* cells;

	Game(int, int, LifeRules*);

	void initGrid();

	void step();

	~Game();
};

