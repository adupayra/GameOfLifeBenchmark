#include "GameCPUThreads.h"

void GameCPUThreads::process()
{
	std::vector<std::thread> threads;

	int i = 0;
	for (i = 0; i < m_nThreads - 1; i++) {
		int index = i * m_cellsPerThread;
		threads.emplace_back(std::thread(&GameCPUThreads::processCells, this, index, index + m_cellsPerThread));
	}
	threads.emplace_back(std::thread(&GameCPUThreads::processCells, this, (m_nThreads - 1) * m_cellsPerThread, m_nbCells - 1));

	for (std::thread& t : threads) {
		t.join();
	}

	std::swap(m_cells, m_newCells);
}

void GameCPUThreads::processCells(int start, int end)
{
	int nbNeighbours = 0;
	for (int i = start; i < end; i++) {
		nbNeighbours = getAliveNeighbours(i);
		m_newCells[i] = m_rules->isAlive(m_cells[i], nbNeighbours);
	}
}

GameCPUThreads::GameCPUThreads(int dimension, int cellsPerDim): Game(dimension, cellsPerDim)
{
	m_nThreads = std::thread::hardware_concurrency();
	m_cellsPerThread = m_nbCells / m_nThreads;
}
