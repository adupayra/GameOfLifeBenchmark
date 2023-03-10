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


	virtual void process() = 0;

public:
	int getAliveNeighbours(int cell);
	
	LifeRules* getRules() { return m_rules; }
	const uint8_t* getCells() { return m_cells; }

	Game(int, int);

	static std::vector<int> getNeighboursIndices(int cell, int cellsPerDim);


	void initGrid();

	void step();

	~Game();
};

