#include "ProcessBase.h"

ProcessBase::ProcessBase(LifeRules* rules, int nbCells, int dimension, int cellsPerDim)
{
	ProcessBase::cellsPerDim = cellsPerDim;
	ProcessBase::dimension = dimension;
	ProcessBase::nbCells = nbCells;
	ProcessBase::rules = rules;
	ProcessBase::newCells = new uint8_t[nbCells];
}

ProcessBase::~ProcessBase()
{
	delete rules;
}
