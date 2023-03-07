#pragma once
#include <stdint.h>
#include "LifeRules.h"

class ProcessBase
{
protected:
	int nbCells, dimension, cellsPerDim;
	LifeRules* rules;
	uint8_t* newCells;
public:
	ProcessBase(LifeRules* rules, int nbCells, int dimension, int cellsPerDim);
	~ProcessBase();
	virtual uint8_t* process(uint8_t* cell) = 0;
};

