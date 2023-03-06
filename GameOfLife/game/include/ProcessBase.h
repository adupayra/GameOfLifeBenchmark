#pragma once
#include <stdint.h>
#include "LifeRules.h"

class ProcessBase
{
protected:
	int nbCells, dimension, cellsPerDim;
	LifeRules* rules;
public:
	ProcessBase(LifeRules* rules, int nbCells, int dimension, int cellsPerDim);
	~ProcessBase();
	virtual void process(uint8_t* cell) = 0;
};

