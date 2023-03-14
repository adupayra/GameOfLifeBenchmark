#include "GPUFunctions.cuh"
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <algorithm>
#include <iostream>

void gpuAssert(cudaError_t code)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code));
		exit(EXIT_FAILURE);
	}
}

__global__ void processCellKernel(uint8_t* cells, uint8_t* newCells, int dimensions, int cellsPerDim, int nbCells) {
	int cellID = threadIdx.x + blockIdx.x * blockDim.x;

	int nbNeighbours = 0;

	int colNb = cellID % cellsPerDim;
	int rowNb = cellID / cellsPerDim;
	int newCell = cellID + 1;

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
	
	bool newValue = false;
	if (cells[cellID]) {
		newValue = nbNeighbours == 2 || nbNeighbours == 3;
	} else
		newValue = nbNeighbours == 3;

	newCells[cellID] = newValue;
}


void processCells(uint8_t*& cells, uint8_t*& devCells, uint8_t*& devNewCells, int dimensions, int cellsPerDim, int nbCells, int nbBlocks, int nbThreads) {

	processCellKernel << <nbBlocks, nbThreads >> > (devCells, devNewCells, dimensions, cellsPerDim, nbCells);
	gpuAssert(cudaPeekAtLastError());
	gpuAssert(cudaDeviceSynchronize());
	gpuAssert(cudaMemcpy(cells, devNewCells, nbCells, cudaMemcpyDeviceToHost));
	std::swap(devCells, devNewCells);

}