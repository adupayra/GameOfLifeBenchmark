#pragma once
#include "LifeRules.h"
#include <vector>

class Game
{
private:
	int dimension;
	int nbCells;
	uint8_t* cells;
	std::vector<int> cellsToChange;
	LifeRules* rules;

public:
	
	Game(int, int, LifeRules*);

	void initGrid();

	void step();

	~Game();
};

