#pragma once
#include <stdint.h>
#include "ProcessBase.h"

class ProcessGPU: public ProcessBase
{
public:
	ProcessGPU(LifeRules* rules, int nbCells, int dimension, int cellsPerDim) : ProcessBase(rules, nbCells, dimension, cellsPerDim) {}

	void process(uint8_t* cells);
};

