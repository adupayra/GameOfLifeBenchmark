#include "Game.h"
#include <random>
#include <cmath>
#include <iostream>

Game::Game(int dimension, int cellsPerDim, LifeRules* rules) {
	Game::dimension = dimension;
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
	cellsToChange = rules->process(cells, nbCells);
	int j = 0;
	for (int i = 0; i < cellsToChange.size(); ++i) {
		j = cellsToChange[i];
		cells[j] = 1 - cells[j];
	}
}