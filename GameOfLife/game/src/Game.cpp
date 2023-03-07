#include "Game.h"
#include <random>
#include <cmath>
#include <iostream>
#include "ClassicRules2D.h"
#include "ProcessCPU.h"
#include "ProcessCPUmulti.h"
#include "ProcessGPU.h"

Game::Game(int dimension, int cellsPerDim, ProcessMode processMode) {
	Game::dimension = dimension;
	Game::cellsPerDim = cellsPerDim;
	Game::nbCells = pow(cellsPerDim, dimension);
	LifeRules* rules = NULL;
	Game::processType = NULL;

	if(dimension == 2)
		rules = new ClassicRules2D();
	switch (processMode) {
	case CPU:
		processType = new ProcessCPU(rules, nbCells, dimension, cellsPerDim);
		break;
	case CPUMulti:
		processType = new ProcessCPUmulti(rules, nbCells, dimension, cellsPerDim);
		break;
	}
	Game::cells = new uint8_t[nbCells];

}

void Game::initGrid() {
	float r = 0;
	float threshold = 0.3f;
	for (int i = 0; i < nbCells; i++) {
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (r < threshold) {
			cells[i] = 1;
		}
		else {
			cells[i] = 0;
		}
	}
}

Game::~Game() {
	delete Game::cells;
	delete Game::processType;
}

void Game::step() {
	cells = processType->process(cells);

}


std::vector<int> Game::getNeighbours(int cell, int cellsPerDim) {

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
 