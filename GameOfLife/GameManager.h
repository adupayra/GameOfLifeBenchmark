#pragma once

#include "GraphicsDisplay.h"
#include "Game.h"
#include "ProcessData.h"

class GameManager
{
private:
	GraphicsDisplay* m_graphicsDisplay;

	Game* m_gameInstance;

	bool m_isBenchmarking;

	double m_meanTime;

	ProcessData* m_processData;

public:
	GameManager(int, int, ProcessMode, bool benchmarking = false, int gpuThreads = 256, double timeout = 500, int iterations = 500);

	const ProcessData* getProcessData() { return m_processData; }

	double getMeantime() { return m_meanTime;}

	void run();

	bool runBench(int, double);
	
	~GameManager();
};

