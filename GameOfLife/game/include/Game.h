#pragma once
#include "LifeRules.h"
#include <vector>

class Game
{
protected:
	int m_dimension;
	int m_nbCells;
	int m_cellsPerDim;
	//ProcessBase *m_processType;
	LifeRules* m_rules;
	uint8_t* m_cells;
	uint8_t* m_newCells;

	int getAliveNeighbours(int cell);

	virtual void process() = 0;

public:
	
	const uint8_t* getCells() { return m_cells; }

	Game(int, int);

	static std::vector<int> getNeighboursIndices(int cell, int cellsPerDim);


	void initGrid();

	void step();

	~Game();
};

