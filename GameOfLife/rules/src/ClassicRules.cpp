#include "ClassicRules.h"
#include <iostream>

std::vector<int> ClassicRules::process(uint8_t* cells, int nbCells) {
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

	return cellsToChange;
}