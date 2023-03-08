#include "ProcessCPU.h"
#include <vector>
#include "Game.h"
#include <iostream>

//uint8_t* ProcessCPU::process(uint8_t* cells)
//{
//	// This function only update the grid relatively to the cells that are alive
//	std::vector<int> cellsToChange;
//	std::vector<int> neighbours;
//	std::vector<int> deadCellsNeighbours;
//	int counter = 0;
//	int deadCellCounter = 0;
//	for (int i = 0; i < nbCells; ++i) {
//		if (cells[i] == 1) {
//			neighbours = Game::getNeighbours(i, cellsPerDim);
//
//			for (int neighbour : neighbours) {
//				if (cells[neighbour] == 1) {
//					++counter;
//				}
//				else {
//					deadCellsNeighbours = Game::getNeighbours(neighbour, cellsPerDim);
//					for (int deadCellNeighbour : deadCellsNeighbours) {
//						if (cells[deadCellNeighbour] == 1) {
//							++deadCellCounter;
//						}
//					}
//					if ((rules->isAlive(cells[neighbour], deadCellCounter) + cells[neighbour]) % 2 == 1)
//						cellsToChange.push_back(neighbour);
//					deadCellCounter = 0;
//				}
//			}
//			if ((rules->isAlive(cells[i], counter) + cells[i]) % 2 == 1)
//				cellsToChange.push_back(i);
//			counter = 0;
//		}
//	}
//
//	int j = 0;
//	for (int i = 0; i < cellsToChange.size(); ++i) {
//		j = cellsToChange[i];
//		cells[j] = 1 - cells[j];
//	}
//	return cells;
//}

//
//uint8_t* ProcessCPU::process(uint8_t* cells) {
//	std::vector<int> nearestNeighbours;
//	int nbNeighbours = 0;
//	for (int i = 0; i < nbCells; ++i) {
//		nearestNeighbours = Game::getNeighbours(i, cellsPerDim);
//		for (int j = 0; j < nearestNeighbours.size(); ++j) {
//			nbNeighbours += cells[nearestNeighbours[j]];
//		}
//		newCells[i] = rules->isAlive(cells[i], nbNeighbours);
//		nbNeighbours = 0;
//	}
//
//	std::swap(cells, newCells);
//	return cells;
//}

uint8_t* ProcessCPU::process(uint8_t* cells)
{


	for (int i = 0; i < nbCells; ++i) {
		//std::vector<int> nearestNeighbours;
		//std::vector<int> neighbours(8);
		int nbNeighbours = 0;

		//std::vector<int> neighbours(8);

		int colNb = i % cellsPerDim;
		int rowNb = i / cellsPerDim;
		int newCell = i + 1;

		int x0 = (rowNb - 1 + cellsPerDim) % cellsPerDim;
		int x2 = (rowNb + 1) % cellsPerDim;
		int y0 = (colNb - 1 + cellsPerDim) % cellsPerDim;
		int y2 = (colNb + 1) % cellsPerDim;

		nbNeighbours += cells[x0 * cellsPerDim + y0];
		nbNeighbours += cells[x0 * cellsPerDim + colNb];
		nbNeighbours += cells[x0 * cellsPerDim + y2];
		nbNeighbours += cells[rowNb * cellsPerDim + y0];
		nbNeighbours += cells[rowNb * cellsPerDim + y2];
		nbNeighbours += cells[x2 * cellsPerDim + y0];
		nbNeighbours += cells[x2 * cellsPerDim + colNb];
		nbNeighbours += cells[x2 * cellsPerDim + y2];


		newCells[i] = rules->isAlive(cells[i], nbNeighbours);
		nbNeighbours = 0;
	}


	std::swap(cells, newCells);
	return cells;
}