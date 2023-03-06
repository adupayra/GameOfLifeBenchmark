#pragma once
#include "LifeRules.h"

class ClassicRules : public LifeRules
{
public:
	ClassicRules(int dimensions, int cellsPerDim, ProcessMode processMode=CPU) : LifeRules(dimensions, cellsPerDim, processMode) {}
	void process(uint8_t*, int) override;
	bool isAlive(uint8_t cell, int nbNeighbours) override;
};

