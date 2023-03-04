#pragma once
#include <vector>
#include "ProcessEnum.h"

class LifeRules
{
protected:
	int dimensions;
	int cellsPerDim;

public:
	ProcessMode processMode;
	LifeRules(int, int, ProcessMode);
	virtual std::vector<int> process(uint8_t*, int) = 0;
	std::vector<int> getNeighbours(int);

};

