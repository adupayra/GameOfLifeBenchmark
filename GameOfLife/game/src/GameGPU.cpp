#include "GameGPU.h"
#include "cuda_runtime.h"
#include "GPUfunctions.cuh"

GameGPU::GameGPU(int dimensions, int cellsPerDim) : Game(dimensions, cellsPerDim)
{
	cudaMalloc((void**)&m_devCells, m_nbCells);
	cudaMalloc((void**)&m_devNewCells, m_nbCells);

	cudaMemcpy(m_devCells, m_cells, m_nbCells, cudaMemcpyHostToDevice);
	m_nbThreads = 256;
	m_nbBlocks = cellsPerDim * cellsPerDim / m_nbThreads;
		
}

GameGPU::~GameGPU()
{
	cudaFree(m_devCells);
	cudaFree(m_devNewCells);
}

#include <iostream>
void GameGPU::process()
{
	processCells(m_cells, m_devCells, m_devNewCells, m_dimension, m_cellsPerDim, m_nbCells, m_nbBlocks, m_nbThreads);
}

