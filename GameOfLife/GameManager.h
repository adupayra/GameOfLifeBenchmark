#pragma once

#include "GraphicsDisplay.h"
#include "Game.h"
#include "ProcessData.h"

class GameManager
{
private:
	GraphicsDisplay* m_graphicsDisplay;

	Game* m_gameInstance;

	bool m_isBenchmarking = false;

	ProcessData* m_processData;

public:
	GameManager(int, int, ProcessMode, bool benchmarking = false, int gpuThreads = 256, double timeout = 500, int iterations = 500);

	void run();

	ProcessData runBench(int, double);
	
	~GameManager();
};

