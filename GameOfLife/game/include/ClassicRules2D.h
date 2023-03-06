#pragma once
#include "LifeRules.h"

class ClassicRules2D : public LifeRules
{
public:
	bool isAlive(uint8_t cell, int nbNeighbours) override;
};

