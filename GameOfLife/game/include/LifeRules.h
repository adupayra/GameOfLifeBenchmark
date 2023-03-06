#pragma once
#include <vector>
#include "ProcessEnum.h"

class LifeRules
{

public:
	virtual bool isAlive(uint8_t cell, int nbNeighbours) = 0;

};

