#include "ProcessBase.h"

ProcessBase::ProcessBase(LifeRules* rules, int nbCells, int dimension, int cellsPerDim)
{
	ProcessBase::cellsPerDim = cellsPerDim;
	ProcessBase::dimension = dimension;
	ProcessBase::nbCells = nbCells;
	ProcessBase::rules = rules;
}

ProcessBase::~ProcessBase()
{
	delete rules;
}
