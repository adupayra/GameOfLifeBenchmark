#include "GameManager.h"
#include "Graphics2D.h"
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <GameCPU.h>
#include <GameCPUThreads.h>
#include <GameCPUppl.h>
#include <GameCPUAlt.h>

GameManager::GameManager(int dimension, int cellsPerDim, ProcessMode processMode) {

	if (dimension != 3 && dimension != 2) {
		throw "Dimensions different than 2 and 3 are not handled";
	}

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
	default:
		GameManager::m_gameInstance = new GameCPU(dimension, cellsPerDim);
	}

	if(dimension == 2)
		GameManager::m_graphicsDisplay = new Graphics2D(600, 512, dimension, cellsPerDim);

	m_gameInstance->initGrid();

	run();
}

GameManager::~GameManager() {
	delete m_gameInstance;
	delete m_graphicsDisplay;
}

void GameManager::run() {
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;

	int i = 1;
	while (!m_graphicsDisplay->m_windowManager->isClosedState()) {
		std::cout << "Iteration " << i << std::endl;

		auto t1 = high_resolution_clock::now();
		m_gameInstance->step();
		auto t2 = high_resolution_clock::now();

		duration<double, std::milli> ms_double = t2 - t1;
		std::cout << "Cells update time: " << ms_double.count() << "ms\n";
		system("CLS");

		m_graphicsDisplay->render(m_gameInstance->getCells());
		i++;
	}
}