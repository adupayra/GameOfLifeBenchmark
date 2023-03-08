#include "GameCPUppl.h"
#include <ppl.h>


void GameCPUppl::process()
{
	Concurrency::parallel_for(0, m_nbCells, [&](int i) {
		int nbNeighbours = getAliveNeighbours(i);
		m_newCells[i] = m_rules->isAlive(m_cells[i], nbNeighbours);
		});

	std::swap(m_cells, m_newCells);
}
