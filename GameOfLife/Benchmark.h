#pragma once
#include "GameManager.h"

class Benchmark
{
private:
	std::vector<ProcessMode> m_benchmarkedmodes;
	int m_seed;

public:
	Benchmark(int dimension, std::vector<ProcessMode> modes, int firstSize, int lastSize, bool gpuThreadsbm = false, int gpuThreads = 256, int iterations = 500, float timeout = 500, int sizeStep = 500, int seed = 31231);

};

