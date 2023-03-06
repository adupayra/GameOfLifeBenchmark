#include "ProcessCPU.h"
#include <vector>
#include "Game.h"

void ProcessCPU::process(uint8_t* cells)
{
	// This function only update the grid relatively to the cells that are alive
	std::vector<int> cellsToChange;
	std::vector<int> neighbours;
	std::vector<int> deadCellsNeighbours;
	int counter = 0;
	int deadCellCounter = 0;
	for (int i = 0; i < nbCells; ++i) {
		if (cells[i] == 1) {
			neighbours = Game::getNeighbours(i, cellsPerDim);

			for (int neighbour : neighbours) {
				if (cells[neighbour] == 1) {
					++counter;
				}
				else {
					deadCellsNeighbours = Game::getNeighbours(neighbour, cellsPerDim);
					for (int deadCellNeighbour : deadCellsNeighbours) {
						if (cells[deadCellNeighbour] == 1) {
							++deadCellCounter;
						}
					}
					if ((rules->isAlive(cells[neighbour], deadCellCounter) + cells[neighbour]) % 2 == 1)
						cellsToChange.push_back(neighbour);
					deadCellCounter = 0;
				}
			}
			if ((rules->isAlive(cells[i], counter) + cells[i]) % 2 == 1)
				cellsToChange.push_back(i);
			counter = 0;
		}
	}

	int j = 0;
	for (int i = 0; i < cellsToChange.size(); ++i) {
		j = cellsToChange[i];
		cells[j] = 1 - cells[j];
	}
}
