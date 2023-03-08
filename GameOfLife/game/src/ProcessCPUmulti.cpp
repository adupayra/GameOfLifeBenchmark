#include "ProcessCPUmulti.h"
#include "Game.h"
#include <iostream>
#include <ppl.h>
#include <array>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

static int getAliveNeighbours(uint8_t* cells, int i, int cellsPerDim)
{
	int nbNeighbours = 0;

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

	return nbNeighbours;
}

void ProcessCPUmulti::processCells(uint8_t* cells, int start, int end)
{
	std::vector<int> nearestNeighbours;
	int nbNeighbours = 0;
	for (int i = start; i < end; i++) {
		int nbNeighbours = 0;

		//int colNb = i % cellsPerDim;
		//int rowNb = i / cellsPerDim;
		//int newCell = i + 1;

		//int x0 = (rowNb - 1 + cellsPerDim) % cellsPerDim;
		//int x2 = (rowNb + 1) % cellsPerDim;
		//int y0 = (colNb - 1 + cellsPerDim) % cellsPerDim;
		//int y2 = (colNb + 1) % cellsPerDim;

		//nbNeighbours += cells[x0 * cellsPerDim + y0];
		//nbNeighbours += cells[x0 * cellsPerDim + colNb];
		//nbNeighbours += cells[x0 * cellsPerDim + y2];
		//nbNeighbours += cells[rowNb * cellsPerDim + y0];
		//nbNeighbours += cells[rowNb * cellsPerDim + y2];
		//nbNeighbours += cells[x2 * cellsPerDim + y0];
		//nbNeighbours += cells[x2 * cellsPerDim + colNb];
		//nbNeighbours += cells[x2 * cellsPerDim + y2];

		nbNeighbours = getAliveNeighbours(cells, i, cellsPerDim);
		newCells[i] = rules->isAlive(cells[i], nbNeighbours);
		nbNeighbours = 0;
	}
}


ProcessCPUmulti::ProcessCPUmulti(LifeRules* rules, int nbCells, int dimension, int cellsPerDim) : ProcessBase(rules, nbCells, dimension, cellsPerDim)
{
	nThreads = std::thread::hardware_concurrency();
	cellsPerThread = nbCells / nThreads;
	threadPool.resize(nThreads);
}

//uint8_t* ProcessCPUmulti::process(uint8_t* cells)
//{
//
//
//	Concurrency::parallel_for(0, nbCells, [&](int index) {
//
//		int nbNeighbours = 0;
//
//		int colNb = index % cellsPerDim;
//		int rowNb = index / cellsPerDim;
//		int newCell = index + 1;
//
//		int x0 = (rowNb - 1 + cellsPerDim) % cellsPerDim;
//		int x2 = (rowNb + 1) % cellsPerDim;
//		int y0 = (colNb - 1 + cellsPerDim) % cellsPerDim;
//		int y2 = (colNb + 1) % cellsPerDim;
//
//		nbNeighbours += cells[x0 * cellsPerDim + y0];
//		nbNeighbours += cells[x0 * cellsPerDim + colNb];
//		nbNeighbours += cells[x0 * cellsPerDim + y2];
//		nbNeighbours += cells[rowNb * cellsPerDim + y0];
//		nbNeighbours += cells[rowNb * cellsPerDim + y2];
//		nbNeighbours += cells[x2 * cellsPerDim + y0];
//		nbNeighbours += cells[x2 * cellsPerDim + colNb];
//		nbNeighbours += cells[x2 * cellsPerDim + y2];
//
//		newCells[index] = rules->isAlive(cells[index], nbNeighbours);
//		nbNeighbours = 0;
//		});
//
//	std::swap(cells, newCells);
//	return cells;
//}

uint8_t* ProcessCPUmulti::process(uint8_t* cells)
{
	int i = 0;
	for (i = 0; i < nThreads - 1; i++) {
		int index = i * cellsPerThread;
		threadPool[i] = std::thread(&ProcessCPUmulti::processCells, this, cells, index, index + cellsPerThread);
	}
	threadPool[i] = std::thread(&ProcessCPUmulti::processCells, this, cells, (nThreads - 1) * cellsPerThread, nbCells - 1);

	for (auto& th : threadPool) {
		th.join();
	}

	std::swap(cells, newCells);
	return cells;
}

