#include "GameGPU.h"
#include "cuda_runtime.h"
#include "GPUfunctions.cuh"
#include <iostream>

GameGPU::GameGPU(int dimensions, int cellsPerDim, int nbThreads) : Game(dimensions, cellsPerDim)
{
	gpuAssert(cudaMalloc((void**)&m_devCells, m_nbCells));
	gpuAssert(cudaMalloc((void**)&m_devNewCells, m_nbCells));

	gpuAssert(cudaMemcpy(m_devCells, m_cells, m_nbCells, cudaMemcpyHostToDevice));
	m_nbThreads = nbThreads;
	m_nbBlocks = cellsPerDim * cellsPerDim / m_nbThreads;
		
}

GameGPU::~GameGPU()
{
	gpuAssert(cudaFree(m_devCells));
	gpuAssert(cudaFree(m_devNewCells));
}

void GameGPU::process()
{
	processCells(m_cells, m_devCells, m_devNewCells, m_dimension, m_cellsPerDim, m_nbCells, m_nbBlocks, m_nbThreads);
}

