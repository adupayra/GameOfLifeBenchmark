#include "Game.h"
#include <random>
#include <cmath>
#include <iostream>

Game::Game(int dimension, int cellsPerDim, LifeRules* rules) {
	Game::dimension = dimension;
	Game::cellsPerDim = cellsPerDim;
	Game::nbCells = pow(cellsPerDim, dimension);
	Game::rules = rules;
	Game::cells = new uint8_t[nbCells];

}



void Game::initGrid() {
	float r = 0;
	float threshold = 0.3;
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
	delete Game::rules;
	delete Game::cells;
}

void Game::step() {
	process(cells, nbCells);
}

void Game::process(uint8_t* cells, int nbCells) {
	std::vector<int> cellsToChange;
	std::vector<int> neighbours;
	std::vector<int> deadCellsNeighbours;
	int counter = 0;
	int deadCellCounter = 0;
	for (int i = 0; i < nbCells; ++i) {
		if (cells[i] == 1) {
			neighbours = getNeighbours(i);

			for (int neighbour : neighbours) {
				if (cells[neighbour] == 1) {
					++counter;
				}
				else {
					deadCellsNeighbours = getNeighbours(neighbour);
					for (int deadCellNeighbour : deadCellsNeighbours) {
						if (cells[deadCellNeighbour] == 1) {
							++deadCellCounter;
						}
					}
					if (deadCellCounter == 3) {
						cellsToChange.push_back(neighbour);
					}
					deadCellCounter = 0;
				}
			}
			if (counter != 2 && counter != 3) {
				cellsToChange.push_back(i);
			}
			counter = 0;
		}
	}

	int j = 0;
	for (int i = 0; i < cellsToChange.size(); ++i) {
		j = cellsToChange[i];
		cells[j] = 1 - cells[j];
	}
}

std::vector<int> Game::getNeighbours(int cell) {

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