#pragma once
#include "LifeRules.h"
#include "ProcessBase.h"
#include <vector>

class Game
{
private:
	int dimension;
	int nbCells;
	int cellsPerDim;
	std::vector<int> cellsToChange;
	ProcessBase *processType;
	uint8_t* cells;


public:
	
	const uint8_t* getCells() { return cells; }

	Game(int, int, ProcessMode);

	static std::vector<int> getNeighbours(int cell, int cellsPerDim);

	void initGrid();

	void step();

	~Game();
};

