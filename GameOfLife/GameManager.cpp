#include "GameManager.h"
#include "Graphics2D.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <GameCPU.h>
#include <GameCPUThreads.h>
#include <GameCPUppl.h>
#include <GameCPUAlt.h>
#include <GameCPUThreadP.h>
#include <GameGPU.h>

GameManager::GameManager(int dimension, int cellsPerDim, ProcessMode processMode, bool benchmarking, int gpuThreads, double timeout, int iterations) {

	if (dimension != 3 && dimension != 2) {
		throw "Dimensions different than 2 and 3 are not handled";
	}

	m_isBenchmarking = benchmarking;

	switch (processMode)
	{
	case CPU:
		GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
		break;
	case CPUAlt:
		if (dimension != 2) {
			std::cerr << "CPUAlt is not available in 3D, switching with CPU" << std::endl;
			GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
			processMode = CPU;
		}
		else {
			GameManager::m_gameInstance = new GameCPUAlt(dimension, cellsPerDim);
		}
		break;
	case CPUThreads:
		GameManager::m_gameInstance = new GameCPUThreads(dimension, cellsPerDim);
		break;
	case CPUppl:
		GameManager::m_gameInstance = new GameCPUppl(dimension, cellsPerDim);
		break;
	case CPUThreadP:
		GameManager::m_gameInstance = new GameCPUThreadP(dimension, cellsPerDim);
		break;
	case GPU:
		GameManager::m_gameInstance = new GameGPU(dimension, cellsPerDim, gpuThreads);
		break;
	default:
		std::cerr << "Requested process mode wasn't found, loading CPU" << std::endl;
		GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
		processMode = CPU;
	}

	m_graphicsDisplay = NULL;
	if (!benchmarking) {
		if (dimension == 2)
			GameManager::m_graphicsDisplay = new Graphics2D(600, 512, dimension, cellsPerDim);
	}

	m_processData = new ProcessData(processMode);
}

GameManager::~GameManager() {
	delete m_gameInstance;
	delete m_graphicsDisplay;
	delete m_processData;
}

void GameManager::run() {

	int i = 1;
	while (!m_graphicsDisplay->m_windowManager->isClosedState()) {

		//std::cout << "Iteration " << i << std::endl;

		m_processData->startMeasurements();
		m_gameInstance->step();
		m_processData->endMeasurements();
		std::cout << "CPU Usage: " << m_processData->getCpuUsage() << std::endl;
		std::cout << "Cells update time: " << m_processData->getExecTime() << "ms\n";

		m_graphicsDisplay->render(m_gameInstance->getCells());
		i++;
	}
}

ProcessData GameManager::runBench(int iterations, double timeout) {
	
	int i = 0;
	while (i < iterations) {
		m_processData->startMeasurements();
		m_gameInstance->step();
		m_processData->endMeasurements();
		i++;
	}
	m_processData->computeMeans();

	return *m_processData;
}