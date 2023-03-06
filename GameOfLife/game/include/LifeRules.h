#pragma once
#include <vector>
#include "ProcessEnum.h"

class LifeRules
{
protected:
	int dimensions;
	int cellsPerDim;

public:
	virtual bool isAlive(uint8_t cell, int nbNeighbours) = 0;
	ProcessMode processMode;
	LifeRules(int, int, ProcessMode);
	virtual void process(uint8_t*, int) = 0;
	std::vector<int> getNeighbours(int);

};

