#pragma once
#include "ProcessBase.h"
#include <stdint.h>
#include <thread>

class ProcessCPUmulti: public ProcessBase
{
private:
	unsigned int nThreads;
	unsigned int cellsPerThread;
	void processCells(uint8_t* cells, int start, int end);
	//uint8_t* currentCells;
	void processCell(int);
	std::vector<std::thread> threadPool;

public:
	ProcessCPUmulti(LifeRules* rules, int nbCells, int dimension, int cellsPerDim);

	uint8_t* process(uint8_t* cells);
};

