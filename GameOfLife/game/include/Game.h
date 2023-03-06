#pragma once
#include "LifeRules.h"
#include <vector>

class Game
{
private:
	int dimension;
	int nbCells;
	int cellsPerDim;
	std::vector<int> cellsToChange;
	LifeRules* rules;
	uint8_t* cells;


public:
	
	uint8_t* getCells() { return cells; }

	Game(int, int, LifeRules*);
	
	void process(uint8_t* cells, int nbCells);

	std::vector<int> getNeighbours(int cell);

	void initGrid();

	void step();

	~Game();
};

