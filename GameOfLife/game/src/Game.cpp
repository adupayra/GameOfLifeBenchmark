#include "Game.h"
#include <random>
#include <cmath>
#include <iostream>
#include "ClassicRules2D.h"


int Game::getAliveNeighbours(int i)
{
	int nbNeighbours = 0;

	int colNb = i % m_cellsPerDim;
	int rowNb = i / m_cellsPerDim;
	int newCell = i + 1;

	int x0 = (rowNb - 1 + m_cellsPerDim) % m_cellsPerDim;
	int x2 = (rowNb + 1) % m_cellsPerDim;
	int y0 = (colNb - 1 + m_cellsPerDim) % m_cellsPerDim;
	int y2 = (colNb + 1) % m_cellsPerDim;

	nbNeighbours += m_cells[x0 * m_cellsPerDim + y0];
	nbNeighbours += m_cells[x0 * m_cellsPerDim + colNb];
	nbNeighbours += m_cells[x0 * m_cellsPerDim + y2];
	nbNeighbours += m_cells[rowNb * m_cellsPerDim + y0];
	nbNeighbours += m_cells[rowNb * m_cellsPerDim + y2];
	nbNeighbours += m_cells[x2 * m_cellsPerDim + y0];
	nbNeighbours += m_cells[x2 * m_cellsPerDim + colNb];
	nbNeighbours += m_cells[x2 * m_cellsPerDim + y2];

	return nbNeighbours;
}

Game::Game(int dimension, int cellsPerDim) {
	Game::m_dimension = dimension;
	Game::m_cellsPerDim = cellsPerDim;
	Game::m_nbCells = pow(cellsPerDim, dimension);
	m_rules = NULL;

	if(dimension == 2)
		m_rules = new ClassicRules2D();

	Game::m_cells = new uint8_t[m_nbCells];
	Game::m_newCells = new uint8_t[m_nbCells];

	initGrid();
}

void Game::initGrid() {
	float r = 0;
	float threshold = 0.3f;
	for (int i = 0; i < m_nbCells; i++) {
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		if (r < threshold) {
			m_cells[i] = 1;
		}
		else {
			m_cells[i] = 0;
		}
	}
}

Game::~Game() {
	delete Game::m_cells;
	delete Game::m_newCells;
	delete Game::m_rules;
}

void Game::step() {
	process();

}


std::vector<int> Game::getNeighboursIndices(int cell, int cellsPerDim) {

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
 