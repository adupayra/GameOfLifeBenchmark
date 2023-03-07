#pragma once
#include <stdint.h>
#include "ProcessBase.h"

class ProcessCPU: public ProcessBase
{
public:
	ProcessCPU(LifeRules* rules, int nbCells, int dimension, int cellsPerDim) : ProcessBase(rules, nbCells, dimension, cellsPerDim) {}

	uint8_t* process(uint8_t* cells);
};

