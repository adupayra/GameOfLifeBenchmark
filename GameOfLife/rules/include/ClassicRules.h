#pragma once
#include "LifeRules.h"

class ClassicRules : public LifeRules
{
public:
	ClassicRules(int dimensions, int cellsPerDim, ProcessMode processMode=CPU) : LifeRules(dimensions, cellsPerDim, processMode) {}
	std::vector<int> process(uint8_t*, int) override;
};

