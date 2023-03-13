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
	m_meanTime = 0;
	switch (processMode)
	{
	case CPU:
		GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
		break;
	case CPUAlt:
		if (dimension != 2) {
			std::cerr << "CPUAlt is not available in 3D, switching with CPU" << std::endl;
			GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
		}
		else {
			GameManager::m_gameInstance = new GameCPUAlt(dimension, cellsPerDim);
		}
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
		GameManager::m_gameInstance = new GameGPU(dimension, cellsPerDim);
		break;
	default:
		std::cerr << "Requested process mode wasn't found, loading CPU" << std::endl;
		GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
	}

	if (!benchmarking) {
		if (dimension == 2)
			GameManager::m_graphicsDisplay = new Graphics2D(600, 512, dimension, cellsPerDim);
	}

	m_processData = new ProcessData(processMode);

	//if (benchmarking)
	//	runBench(iterations, timeout);
	//else
	//	run();
}

GameManager::~GameManager() {
	delete m_gameInstance;
	delete m_graphicsDisplay;
	delete m_processData;
}

void GameManager::run() {
	//using std::chrono::high_resolution_clock;
	//using std::chrono::duration_cast;
	//using std::chrono::duration;
	//using std::chrono::milliseconds;

	int i = 1;
	while (!m_graphicsDisplay->m_windowManager->isClosedState()) {

		std::cout << "Iteration " << i << std::endl;


		m_processData->startMeasurements();
		m_gameInstance->step();
		m_processData->endMeasurements();
		std::cout << "CPU Usage: " << m_processData->getCpuUsage() << std::endl;
		std::cout << "Cells update time: " << m_processData->getExecTime() << "ms\n";

		m_graphicsDisplay->render(m_gameInstance->getCells());
		i++;
	}
}

bool GameManager::runBench(int iterations, double timeout) {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;
	
	bool isTimedout = false;
	std::vector<double> times;
	int i = 0;
	while (!isTimedout && i < iterations) {
		//std::cout << "Iteration " << i << std::endl;

		auto t1 = high_resolution_clock::now();
		m_gameInstance->step();
		auto t2 = high_resolution_clock::now();

		duration<double, std::milli> ms_double = t2 - t1;
		if (ms_double.count() > timeout)
			isTimedout = true;
		//std::cout << "Cells update time: " << ms_double.count() << "ms\n";
		times.push_back(ms_double.count());
		i++;
	}

	double sum = 0;
	for (int j = 0; j < times.size(); ++j) {
		sum += times[j];
	}
	//m_processData.m_meanTime = sum / times.size();
	m_meanTime = sum / times.size();
	return isTimedout;
}