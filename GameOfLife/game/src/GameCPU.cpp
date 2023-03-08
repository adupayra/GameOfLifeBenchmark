#include "GameCPU.h"

void GameCPU::process()
{
	int neighbours = 0;
	for (int i = 0; i < m_nbCells; i++) {
		neighbours = getAliveNeighbours(i);
		m_newCells[i] = m_rules->isAlive(m_cells[i], neighbours);
	}
	std::swap(m_cells, m_newCells);
}
