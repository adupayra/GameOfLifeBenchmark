#include "ProcessCPUmulti.h"
#include "Game.h"
#include <iostream>
#include <thread>
#include <ppl.h>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
void ProcessCPUmulti::processCells(uint8_t* cells, int start, int end)
{
	std::vector<int> nearestNeighbours;
	int nbNeighbours = 0;
	for (int i = start; i < end; i++) {
		nearestNeighbours = Game::getNeighbours(i, cellsPerDim);
		for (int j = 0; j < nearestNeighbours.size(); ++j) {
			nbNeighbours += cells[nearestNeighbours[j]];
		}
		newCells[i] = rules->isAlive(cells[i], nbNeighbours);
		nbNeighbours = 0;
	}
}

void ProcessCPUmulti::test(int index) {

}

ProcessCPUmulti::ProcessCPUmulti(LifeRules* rules, int nbCells, int dimension, int cellsPerDim) : ProcessBase(rules, nbCells, dimension, cellsPerDim)
{
	nThreads = std::thread::hardware_concurrency();
	cellsPerThread = nbCells / nThreads;
}

uint8_t* ProcessCPUmulti::process(uint8_t* cells)
{


	Concurrency::parallel_for(0, nbCells, [&](int index) {
		//std::vector<int> nearestNeighbours;
		//std::vector<int> neighbours(8);

		int nbNeighbours = 0;
		//auto t1 = high_resolution_clock::now();

		//nearestNeighbours = Game::getNeighbours(index, cellsPerDim);


		int colNb = index % cellsPerDim;
		int rowNb = index / cellsPerDim;
		int newCell = index + 1;

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
		//auto t2 = high_resolution_clock::now();
		//duration<double, std::milli> ms_double = t2 - t1;
		//std::cout << "Cells update time: " << ms_double.count() << "ms\n";



		//neighbours[0] = x0 * cellsPerDim + y0;
		//neighbours[1] = x0 * cellsPerDim + colNb;
		//neighbours[2] = x0 * cellsPerDim + y2;
		//neighbours[3] = rowNb * cellsPerDim + y0;
		//neighbours[4] = rowNb * cellsPerDim + y2;
		//neighbours[5] = x2 * cellsPerDim + y0;
		//neighbours[6] = x2 * cellsPerDim + colNb;
		//neighbours[7] = x2 * cellsPerDim + y2;


		//for (int j = 0; j < nearestNeighbours.size(); ++j) {
		//	nbNeighbours += cells[nearestNeighbours[j]];
		//}
		newCells[index] = rules->isAlive(cells[index], nbNeighbours);
		nbNeighbours = 0;
		});



	//for (int i = 0; i < nThreads - 1; i++) {
	//	int index = i * cellsPerThread;
	//	threads.push_back(std::thread(&ProcessCPUmulti::processCells, this, cells, index, index + cellsPerThread));
	//}
	//threads.push_back(std::thread(&ProcessCPUmulti::processCells, this, cells, (nThreads - 1) * cellsPerThread, nbCells - 1));

	//for (auto& th : threads) {
	//	th.join();
	//}

	std::swap(cells, newCells);
	return cells;
}

