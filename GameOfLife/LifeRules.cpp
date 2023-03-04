#pragma once
#include "LifeRules.h"
#include "iostream"

LifeRules::LifeRules(int dimensions, int cellsPerDim, ProcessMode processMode=CPU) {
	LifeRules::dimensions = dimensions;
	LifeRules::cellsPerDim = cellsPerDim;
	LifeRules::processMode = processMode;
}

std::vector<int> LifeRules::getNeighbours(int cell) {

	std::vector<int> neighbours(8);


	int colNb = cell % cellsPerDim;
	int rowNb = cell / cellsPerDim;
	int newCell = cell + 1;

	int x0 = (rowNb - 1 + cellsPerDim) % cellsPerDim;
	int x2 = (rowNb + 1) % cellsPerDim;
	int y0 = (colNb - 1 + cellsPerDim) % cellsPerDim;
	int y2 = (colNb + 1) % cellsPerDim;

	neighbours[0] = x0 * cellsPerDim + y0;
	neighbours[1] = x0 * cellsPerDim + colNb;
	neighbours[2] = x0 * cellsPerDim + y2;
	neighbours[3] = rowNb * cellsPerDim + y0;
	neighbours[4] = rowNb * cellsPerDim + y2;
	neighbours[5] = x2 * cellsPerDim + y0;
	neighbours[6] = x2 * cellsPerDim + colNb;
	neighbours[7] = x2 * cellsPerDim + y2;

	return neighbours;
}