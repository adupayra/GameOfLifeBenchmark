#pragma once

#include "GraphicsDisplay.h"
#include "Game.h"

class GameManager
{
private:
	GraphicsDisplay* m_graphicsDisplay;

	Game* m_gameInstance;

	bool m_isBenchmarking;

	double m_meanTime;

public:
	GameManager(int, int, ProcessMode, bool benchmarking = false, int gpuThreads = 256, double timeout = 500, int iterations = 500);

	double getMeantime() { return m_meanTime;}

	void run();

	void runBench(int, double);
	
	~GameManager();
};

