#include "GameCPUAlt.h"

std::vector<int> GameCPUAlt::getNeighboursIndices(int i)
{
	std::vector<int> neighbours(8);


	int colNb = i % m_cellsPerDim;
	int rowNb = i / m_cellsPerDim;
	int newCell = i + 1;

	int x0 = (rowNb - 1 + m_cellsPerDim) % m_cellsPerDim;
	int x2 = (rowNb + 1) % m_cellsPerDim;
	int y0 = (colNb - 1 + m_cellsPerDim) % m_cellsPerDim;
	int y2 = (colNb + 1) % m_cellsPerDim;

	neighbours[0] = x0 * m_cellsPerDim + y0;
	neighbours[1] = x0 * m_cellsPerDim + colNb;
	neighbours[2] = x0 * m_cellsPerDim + y2;
	neighbours[3] = rowNb * m_cellsPerDim + y0;
	neighbours[4] = rowNb * m_cellsPerDim + y2;
	neighbours[5] = x2 * m_cellsPerDim + y0;
	neighbours[6] = x2 * m_cellsPerDim + colNb;
	neighbours[7] = x2 * m_cellsPerDim + y2;

	return neighbours;
}

void GameCPUAlt::process() {
	// This function only update the grid relatively to the cells that are alive
	std::vector<int> cellsToChange;
	std::vector<int> neighbours;
	std::vector<int> deadCellsNeighbours;
	int counter = 0;
	int deadCellCounter = 0;
	for (int i = 0; i < m_nbCells; ++i) {
		if (m_cells[i] == 1) {
			neighbours = getNeighboursIndices(i);

			for (int neighbour : neighbours) {
				if (m_cells[neighbour] == 1) {
					++counter;
				}
				else {
					deadCellsNeighbours = getNeighboursIndices(neighbour);
					for (int deadCellNeighbour : deadCellsNeighbours) {
						if (m_cells[deadCellNeighbour] == 1) {
							++deadCellCounter;
						}
					}
					if ((m_rules->isAlive(m_cells[neighbour], deadCellCounter) + m_cells[neighbour]) % 2 == 1)
						cellsToChange.push_back(neighbour);
					deadCellCounter = 0;
				}
			}
			if ((m_rules->isAlive(m_cells[i], counter) + m_cells[i]) % 2 == 1)
				cellsToChange.push_back(i);
			counter = 0;
		}
	}

	int j = 0;
	for (int i = 0; i < cellsToChange.size(); ++i) {
		j = cellsToChange[i];
		m_cells[j] = 1 - m_cells[j];
	}
}