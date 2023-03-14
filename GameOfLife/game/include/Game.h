#pragma once
#include "LifeRules.h"
#include <vector>

class Game
{
protected:
	int m_dimension;
	int m_nbCells;
	int m_cellsPerDim;

	LifeRules* m_rules;
	uint8_t* m_cells;
	uint8_t* m_newCells;

	int getAliveNeighbours(int cell);

	virtual void process() = 0;

	void initGrid();

public:
	const uint8_t* getCells() { return m_cells; }

	Game(int, int);


	void step();

	virtual ~Game();
};

